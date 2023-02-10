/*
 * Copyright 2021, Cypress Semiconductor Corporation or a subsidiary of 
 * Cypress Semiconductor Corporation. All Rights Reserved.
 * 
 * This software, associated documentation and materials ("Software"),
 * is owned by Cypress Semiconductor Corporation
 * or one of its subsidiaries ("Cypress") and is protected by and subject to
 * worldwide patent protection (United States and foreign),
 * United States copyright laws and international treaty provisions.
 * Therefore, you may use this Software only as provided in the license
 * agreement accompanying the software package from which you
 * obtained this Software ("EULA").
 * If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
 * non-transferable license to copy, modify, and compile the Software
 * source code solely for use in connection with Cypress's
 * integrated circuit products. Any reproduction, modification, translation,
 * compilation, or representation of this Software except as specified
 * above is prohibited without the express written permission of Cypress.
 *
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
 * reserves the right to make changes to the Software without notice. Cypress
 * does not assume any liability arising out of the application or use of the
 * Software or any product or circuit described in the Software. Cypress does
 * not authorize its products for use in any products where a malfunction or
 * failure of the Cypress product may reasonably be expected to result in
 * significant property damage, injury or death ("High Risk Product"). By
 * including Cypress's product in a High Risk Product, the manufacturer
 * of such system or application assumes all risk of such use and in doing
 * so agrees to indemnify Cypress against all liability.
 */

/** @file
 *
 * Test functions for filesystem which run in the console app
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "typedefs.h"
#include "command_console.h"
#include "command_console_fs.h"
#include "wiced_rtos.h"
#include "wiced_defaults.h"
#include "wiced_osl.h"
#include "wiced_management.h"
#include "wiced_resource.h"
#include "wiced_time.h"
#include "wiced_filesystem.h"
#include "wiced_usb.h"
#include "internal/wiced_filesystem_internal.h"

/******************************************************
 *                      Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/
#define LOCAL_BUFFER_SIZE   (64*1024)

#define SHA1_LENGTH         20              /* Length of the SHA1 hash */

#define MAX_SHA1_LIST_ITEM_COUNT        (100)
#define MAX_BYTE_PER_LINE               (60)
#define MAX_SHA1_EXPECT_LIST_SIZE       (MAX_SHA1_LIST_ITEM_COUNT * MAX_BYTE_PER_LINE)

#define SHA1SUM_READ_TEST
#define SHA1SUM_WRITE_TEST
/* The file can be generated by Windows or Linux using the following command:
 * sha1sum file1 file2 > sha1_expect_list.txt
 */
#define SHA1_EXPECTED_LIST_FILE_NAME    "/sha1_expect_list.txt"
#define SHA1_EXPECTED_LIST_READ_FROM_FILE 1

#define MAX_PATH_LEN        255

#define CHECK_HANDLE_VALIDATION(fs_handle) if ( check_handle_validation(fs_handle) != 0 ) \
                                        { \
                                            printf( "NULL handle pointer found at %s #%d\n", __FILE__, __LINE__ ); \
                                            return 1; \
                                        }



#define CHECK_FS_VALIDATION(status) if ( status != WICED_SUCCESS ) \
                                    { \
                                       printf( "Wiced FS error code (0x%02X) found at %s #%d\n", status, __FILE__, __LINE__ ); \
                                       return 1; \
                                    }

/******************************************************
 *                   Enumerations
 ******************************************************/

/******************************************************
 *                 Type Definitions
 ******************************************************/

/******************************************************
 *                    Structures
 ******************************************************/

/******************************************************
 *               Static Function Declarations
 ******************************************************/
static int check_handle_validation( wiced_filesystem_t* fs_handle );
static void dump_bytes(const uint8_t* bptr, uint32_t len);
static int sw_calc_file_sha1 ( wiced_filesystem_t* filesystem_handle, char* file_name, uint8_t sha1_result[SHA1_LENGTH], wiced_time_t* time_spent );
static int get_expected_sha1sum ( char* expect_file_name, uint8_t sha1_expect_result[SHA1_LENGTH], char* sha1_expect_list );
static int file_compare( wiced_filesystem_t* filesystem_handle, char* file1_name, char* file2_name );
static int write_file( wiced_filesystem_t* filesystem_handle, char* src_file_name, char* dst_file_name, uint32_t local_buffer_size, uint32_t* read_mbps, uint32_t* write_mbps );

/******************************************************
 *               Variable Definitions
 ******************************************************/

#if (SHA1_EXPECTED_LIST_READ_FROM_FILE == 0)
static const char *sha1_expect_list =
"7887fa8ca33b9048a175357e54878a93aab9f1c7 *0.BIN\n"
"42e254e1501f27c1c33495249eebfbf940350f92 *1.BIN\n"
"acbeb623b28e4e982f281c7d0c108d5fa2695c36 *2.BIN\n"
"816b405195719b7a81edae394a2db4a12f992d96 *3.BIN\n"
"c42589ed51ce0b39fa2bf9f6e153ba8b1cf3b853 *4.BIN\n"
"3e5c2d1ad73a705ce2d612ae79ee7f9afbaacfed *5.BIN\n"
"f7740364bb40f05e28b1f601cb4df7f7080c94da *6.BIN\n"
"3aa4120b6d5a4b4ea91533cf7d963f77598b5011 *7.BIN\n"
"85be343ed2c4a44c29eb60d54040d971c6e2b058 *8.BIN\n"
"33e76bc0747b1503f58880a116812ef554c572f3 *9.BIN\n"
"2aafa1b81d20c9b0175912dc1958ac9e6644854f *10.BIN\n"
"e36c040fc9db0647ff7cd41c00c316ad42f042aa *11.BIN\n"
"63b1cb82035684343bc291d62000c57b20deee83 *12.BIN\n"
"50a994dc2b7f61444945daa3424e5b210e26b787 *13.BIN\n"
"ed2a39dae575ade2b93230e294d6bc307d2e76c8 *14.BIN\n"
"7a3ce91dd43ef3eafc98f11057eb2bdcb07c380d *15.BIN\n"
"0c072d4615cd483792ade9cc415e1246bc05cdc8 *16.BIN\n"
"803c909960150707586c9d89335be29c296307dc *17.BIN\n"
"5d2c604cf877e1c84dde2a8c306c7853172e26e1 *18.BIN\n"
"717b5e60bdc2886c74ccb56ae36b97f563056f98 *19.BIN\n"
"da769dde0b7063e7880566d78699bdba5d0fb2f3 *20.BIN\n"
"18251320da6e140ca98912f606e0bcb45df55126 *21.BIN\n"
"67a3fb889b5937237d899942f2435d40aa1765a3 *22.BIN\n"
"1f4a77aaaa09f9978a9b9d00d50fcf144d18e335 *23.BIN\n"
"17bc3528ee1e25ed6e8e9c624aa29d1e9704f5e6 *24.BIN\n"
"9a388647fbf232e1f3dcd52b633ef05d0dcdd016 *25.BIN\n"
"90ca58fa30780d2224f51aa56f66c835b8dbf1d8 *26.BIN\n"
"bae4cdc9c02efbd8d8fefa1b3f6b9d85b12528c5 *27.BIN\n"
"169cb8445d76a318246a2a892afa3a10e4a2a9f9 *28.BIN\n"
"3b216f4d7739ece8e81f1b2f07472e18806b389d *29.BIN\n"
"3cab7cdfda88c73c92740b616d08260e415cf6a7 *30.BIN\n"
"98c3d97621dfa8c29f3433fe82e1d594454ef281 *31.BIN\n"
"bbf7237ee259254341d65a007a1b88e0388cab67 *32.BIN\n"
"1d605585df658d4b86084e1c0b69715800b59e62 *33.BIN\n"
"93dfc1a720e4d93b0937ca2d0564793c1bb78268 *34.BIN\n"
"e2f3c4a005afa05648b24634b37d1ee577dd8f33 *35.BIN\n"
"bcd8c060cb95ea002b29747e11e9e4806b308655 *36.BIN\n"
"2a4533058d41d9771cdde74095e12faf3814433b *37.BIN\n"
"badf5e39516d02629bbdc10ff3e3c2d4e50e59a5 *38.BIN\n"
"6fae30e3051fef4a9153f2bb36607431522140ff *39.BIN\n"
"84ae2b2c6f523d3b08f11b5da7c2be733013988c *40.BIN\n"
"8cd2952d930d64684f7f199753d145dd09c5cfbe *41.BIN\n"
"635ec11c257fd17339aaf95ce373c0ef6bd28dbd *42.BIN\n"
"4aa309c54299cc272a9346c46f2d0e685892bad7 *43.BIN\n"
"52fa13bd222bb09930f59216bd9f28bdaaea3c48 *44.BIN\n"
"027f7c37ec5a951e54dd2524d5de6d2e6d5c1bb9 *45.BIN\n"
"54d2f97ce65806e8383608a4cd6c545b8f2738b7 *46.BIN\n"
"14c664d9cc072f22dcf9e430f6c59119e883b098 *47.BIN\n"
"2f00fcf788036de5cc12bc31c0dffc2cea7bc0b2 *48.BIN\n"
"07a3a29f06d1733c6e8009879223ec4159c29dbc *49.BIN\n"
"0653e09127015670903d67bb4f918c8aa0cb9791 *50.BIN\n"
"364304430346977b3a573aa436e4a67ea63138c0 *51.BIN\n"
"79c8d70dbd69ddb06c68c59a197189c72a0d5058 *52.BIN\n"
"1f63a5927c7e6e69e1f842d67b4be472426a39b9 *53.BIN\n"
"749d82aed7a958ba211bb94d09c71204a01ef5f3 *54.BIN\n"
"922841fca84b585d2030476c523741083793c868 *55.BIN\n"
"fc6a24750085f3e22a5194add37617f4985358d5 *56.BIN\n"
"eed35d84db05488cf92080791e9d12698d683a9e *57.BIN\n"
"209fdde9f6df448ed549d6d88d4d0b8fad664529 *58.BIN\n"
"2e386635d678044d3bf095227a8d4d7e2f572cf1 *59.BIN\n"
"734f3b627bdc68dd34f714c8298eef1577418340 *60.BIN\n"
"31d5416f3bb127519c9027ec9334287128bd0714 *61.BIN\n"
"806c535e300dab38bf6dfdaae96cdb973ba8b8a1 *62.BIN\n"
"1c048e8dc4c11b4e52b26c11789134d3fb498c57 *63.BIN\n"
"e322366ea702601f3f9b0014696fb55241a09acb *64.BIN\n"
"d96d3ec4525d916e6933b97f04902043f070fee4 *65.BIN\n"
"ea92a2592bf487c3c48f8a125d7155caf16126c6 *66.BIN\n"
"f7992b6af0a93ee3e7e2155a940853052cba5b21 *67.BIN\n"
"c49111562586bfe92dbc0adb634f8174d6c8a8fd *68.BIN\n"
"bce367ea2d98f1a6306df7994c8794299f62b2a1 *69.BIN\n"
"646c1fc6e37f36dcad053406824467f896a05363 *70.BIN\n"
"e178b4a7a4acc81cb772dee876e703df1fffc2bb *71.BIN\n"
"22b537d0746e4df8c3a94fc6fc5a2d69924e8f1a *72.BIN\n"
"1435a95ee4c203e0665ce4cc80c19acbaf7d5869 *73.BIN\n"
"574d44a65209638b0ba01238ce3fc3cbbbf34a84 *74.BIN\n"
"1f3f09eaaeded4894eff44c3af9b0d268cf0bfaf *75.BIN\n"
"0ae367ba156b77056e3c06652632ee34527c9db7 *76.BIN\n"
"7dc6b951b88d9cc6c2646317244736abad32ac55 *77.BIN\n"
"9a4c577631be9fdd6631a5a58d1e086e5e0a5569 *78.BIN\n"
"55dbf1b972f7f53740194415a0d4cbe2f2d2c7ce *79.BIN\n"
"04f261225ba93e596bc45fc73683e406096be45c *80.BIN\n"
"3dee2ddf64eeec1dc29fd5f2b2301942d083d838 *81.BIN\n"
"8f0da15ed3f398d0b8860af155c58063bbe717fb *82.BIN\n"
"00b85311abf601fbff4a2357c931f5a9ad829c43 *83.BIN\n"
"56a751a74afaf865bc36ff1835e76152e2f0bbd4 *84.BIN\n"
"8789199226eb2a89d9ba4061aa46aa879e136154 *85.BIN\n"
"2e4a1aa237cd2f57ec46dd48284dcfb36d05d308 *86.BIN\n"
"6c58db03b0e172ab962c26bbd3e6dbca53856a72 *87.BIN\n"
"d7258c179ed1adbb4403690a278f836f8bf628c3 *88.BIN\n"
"3a88b050da37caa5a317f0f6ebb5f0cd63073bc3 *89.BIN\n"
"1c920dfbd350834f1817a6e76b85754d35165521 *90.BIN\n"
"4af47b49198b48280a61d4a227502a1e4168dfd3 *91.BIN\n"
"8110c80cd11ca54ed0e3094cac4911354d081ef2 *92.BIN\n"
"f96792780375057b562d7fc1b59db493bc46ab75 *93.BIN\n"
"7ffe188d35b1bbc6460a6a30f7f71d7f7fd59232 *94.BIN\n"
"d4a55b4669d45bb86dc96c2f171278b5e936b42d *95.BIN\n"
"a88b1acc085a5500f90f5fc85d06e331d8723fbe *96.BIN\n"
"0c16c0c235806a5683370af8a2b67154e14da6ec *97.BIN\n"
"1917910c579a7d4aab7cef8dd2d4ca66082ef0fc *98.BIN\n"
"972493a334d49301291bfcea9652a219b9bee644 *99.BIN\n";
#endif
/******************************************************
 *               Function Definitions
 ******************************************************/
static int check_handle_validation( wiced_filesystem_t* fs_handle )
{
    void* handle = NULL;

#ifdef USING_FATFS
    if ( fs_handle->driver == &wiced_filesystem_driver_fatfs )
    {
        handle = (void*)&fs_handle->data.fatfs.handle;
    }
#endif /* ifdef USING_FATFS */
#ifdef USING_FILEX
    if ( fs_handle->driver == &wiced_filesystem_driver_filex )
    {
        handle = (void*)&fs_handle->data.filex.handle;
    }
#endif /* ifdef USING_FILEX */
#ifdef USING_FILEX_USBX
    if ( fs_handle->driver == &wiced_filesystem_driver_filex_usbx )
    {
        handle = (void*)fs_handle->data.filex_usbx.handle;
    }
#endif /* ifdef USING_FILEX_USBX */

    if ( handle == NULL || *(uint32_t*)handle == 0 )
    {
        return 1;
    }

    return 0;
}

static int write_file( wiced_filesystem_t* filesystem_handle, char* src_file_name, char* dst_file_name, uint32_t local_buffer_size, uint32_t* read_mbps, uint32_t* write_mbps )
{
    uint64_t requested_length = 0, bytes_written = 0, total_length = 0;
    wiced_result_t status;

    wiced_file_t   my_source_file = {0};
    wiced_file_t   my_dest_file = {0};

    wiced_time_t t1, t2, t3, read_time = 0, write_time = 0;

    char* local_buffer = (char*) osl_malloc_align( (uint)local_buffer_size, (uint)PLATFORM_L1_CACHE_SHIFT );
    CHECK_HANDLE_VALIDATION( filesystem_handle );

    /* Open the source file.  */
    status = wiced_filesystem_file_open( filesystem_handle, &my_source_file, src_file_name, WICED_FILESYSTEM_OPEN_FOR_READ );
    CHECK_FS_VALIDATION(status);

    /* Delete the destination file if it exists.  */
    status = wiced_filesystem_file_delete( filesystem_handle, dst_file_name );

    /* Open file for copying.  */
    status = wiced_filesystem_file_open( filesystem_handle, &my_dest_file, dst_file_name, WICED_FILESYSTEM_OPEN_WRITE_CREATE );
    CHECK_FS_VALIDATION(status);

    /* Seek to the beginning to copy over an existing file.  */
    status = wiced_filesystem_file_seek( &my_dest_file, 0, WICED_FILESYSTEM_SEEK_SET );
    CHECK_FS_VALIDATION(status);

    do
    {
        wiced_time_get_time( &t1 );

        /* Read the file in blocks.  */
        status = wiced_filesystem_file_read( &my_source_file, local_buffer, local_buffer_size, &requested_length );
        wiced_time_get_time( &t2 );

        /* Copy the file in blocks */
        status = wiced_filesystem_file_write( &my_dest_file, local_buffer, requested_length, &bytes_written );
        wiced_time_get_time( &t3 );

        total_length += requested_length;
        read_time += t2 - t1;
        write_time += t3 - t2;
    } while (requested_length == local_buffer_size); /* Check if end of file.  */

    free( local_buffer );

    /* Done, return to caller.  */
    status = wiced_filesystem_file_close( &my_source_file );
    CHECK_FS_VALIDATION(status);

    status = wiced_filesystem_file_close( &my_dest_file );
    CHECK_FS_VALIDATION(status);

    if ( read_mbps != NULL && write_mbps != NULL )
    {
        if ( read_time == 0 || write_time == 0 )
        {
            printf( "file size (%llu bytes) is too small to measure tput\n", total_length );
        }
        else
        {
            /* output read/write Mbit/sec */
            *read_mbps = total_length * 8 / read_time / 1000;
            *write_mbps = total_length * 8 / write_time / 1000;
        }
    }

    return ERR_CMD_OK;
}

int file_rw_sha1sum_test (int argc, char* argv[])
{
    char* disk_name     = argc >= 2 ? argv[1] : USB_DISK_STORAGE_MOUNT_NAME;
    char* src_file_name = argc == 4 ? argv[2] : "\\IMAGE.TXT";
    char* dst_file_name = argc == 4 ? argv[3] : "\\COPYFILE.TXT";

    wiced_filesystem_t* filesystem_handle = wiced_filesystem_retrieve_mounted_fs_handle( disk_name );

    if ( write_file( filesystem_handle, src_file_name, dst_file_name, LOCAL_BUFFER_SIZE, NULL, NULL ) == ERR_CMD_OK )
    {
        WPRINT_APP_INFO(("File read/write completed!\n"));

        if ( file_compare( filesystem_handle, src_file_name, dst_file_name ) == 0 )
        {
            WPRINT_APP_INFO(("File compare completed, no error found!\n"));
        }
        else
        {
            WPRINT_APP_INFO(("File compare fail!\n"));
        }
    }
    else
    {
        WPRINT_APP_INFO(("File read/write fail!\n"));
    }

    return ERR_CMD_OK;
}

int file_rw_tput_test (int argc, char* argv[])
{
    char* disk_name     = argc >= 2 ? argv[1] : USB_DISK_STORAGE_MOUNT_NAME;
    char* src_file_name = argc == 4 ? argv[2] : "\\IMAGE.TXT";
    char* dst_file_name = argc == 4 ? argv[3] : "\\COPYFILE.TXT";
    uint32_t local_buffer_size[] = { 64*1024, 32*1024, 16*1024, 8*1024 };
    uint32_t read_mbps, write_mbps;
    int i, j;

    wiced_filesystem_t* filesystem_handle = wiced_filesystem_retrieve_mounted_fs_handle( disk_name );

    for ( i = 0; i < sizeof(local_buffer_size)/sizeof(uint32_t); i++ )
    {
        for ( j = 0; j < 5; j++ )
        {
            if ( write_file( filesystem_handle, src_file_name, dst_file_name, local_buffer_size[i], &read_mbps, &write_mbps ) == ERR_CMD_OK )
            {
                //file_compare( filesystem_handle, src_file_name, dst_file_name );
                printf("burst %ld read %lu Mbit/sec write %lu Mbit/sec\n", local_buffer_size[i], read_mbps, write_mbps );
            }
            else
            {
                break;
            }
        }
    }

    return ERR_CMD_OK;
}

int files_rw_sha1sum_test (int argc, char* argv[])
{
#if (SHA1_EXPECTED_LIST_READ_FROM_FILE == 1)
    wiced_file_t   file_handle = {0};
    wiced_dir_t    dir_handle = {0};
    wiced_dir_entry_type_t entry_type;
    wiced_dir_entry_details_t finfo;
    uint32_t sha1_expect_list_size = 0;
    uint64_t requested_length = 0;
    char *sha1_expect_list = osl_malloc_align( (uint)MAX_SHA1_EXPECT_LIST_SIZE, (uint)PLATFORM_L1_CACHE_SHIFT );
#endif

    wiced_result_t status;
    uint8_t sha1_hash[SHA1_LENGTH], expected_sha1_hash[SHA1_LENGTH];
    wiced_time_t time_spent;

    char current_name[MAX_PATH_LEN];
    char* disk_name = argc >= 2 ? argv[1] : USB_DISK_STORAGE_MOUNT_NAME;

    wiced_filesystem_t* filesystem_handle = wiced_filesystem_retrieve_mounted_fs_handle( disk_name );
    CHECK_HANDLE_VALIDATION( filesystem_handle );

#if (SHA1_EXPECTED_LIST_READ_FROM_FILE == 1)
    /* Check if malloc fails */
    if ( sha1_expect_list == NULL )
    {
        WPRINT_APP_INFO( ( "sha1_expect_list buffer is NULL\n" ) );
        return ERR_UNKNOWN;
    }
    memset( sha1_expect_list, 0, MAX_SHA1_EXPECT_LIST_SIZE );

    /* Open the sha1_expect_list file.  */
    status = wiced_filesystem_file_open( filesystem_handle, &file_handle, SHA1_EXPECTED_LIST_FILE_NAME, WICED_FILESYSTEM_OPEN_FOR_READ );
    CHECK_FS_VALIDATION(status);

    sha1_expect_list_size = 0;
    requested_length = 0;
    do
    {
        /* Read the file in blocks.  */
        status = wiced_filesystem_file_read( &file_handle, sha1_expect_list + requested_length, LOCAL_BUFFER_SIZE, &requested_length );

        sha1_expect_list_size += requested_length;
    } while (requested_length == LOCAL_BUFFER_SIZE); /* Check if end of file.  */

    if ( sha1_expect_list_size > MAX_SHA1_EXPECT_LIST_SIZE )
    {
        WPRINT_APP_INFO( ( "sha1_expect_list buffer overflow (%ld / %d)\n", sha1_expect_list_size, MAX_SHA1_EXPECT_LIST_SIZE ) );
        return ERR_UNKNOWN;
    }

    /* Done, close file.  */
    status = wiced_filesystem_file_close( &file_handle );
    CHECK_FS_VALIDATION(status);
#endif

#ifdef SHA1SUM_READ_TEST
    status = wiced_filesystem_dir_open( filesystem_handle, &dir_handle, "/read" );
    CHECK_FS_VALIDATION(status);

    while ( status == WICED_SUCCESS )
    {
        status = wiced_filesystem_dir_read( &dir_handle, current_name, MAX_PATH_LEN, &entry_type, &finfo );
        if ( status == WICED_SUCCESS && entry_type == WICED_FILESYSTEM_FILE )
        {
            if ( get_expected_sha1sum( current_name, (uint8_t *)expected_sha1_hash, (char *)sha1_expect_list ) != 0 )
            {
                WPRINT_APP_INFO( ( "Read: '%s' not found in %s\n", current_name, SHA1_EXPECTED_LIST_FILE_NAME ) );
                return ERR_UNKNOWN;
            }

            sw_calc_file_sha1( filesystem_handle, current_name, (uint8_t *)sha1_hash, &time_spent );

            if (memcmp(sha1_hash, expected_sha1_hash, SHA1_LENGTH) == 0)
            {
                WPRINT_APP_INFO( ( "Read: '%s' SHA-1 Success (", current_name ) );
                dump_bytes((uint8_t*)sha1_hash, SHA1_LENGTH );
                WPRINT_APP_INFO( ( ") %u ms\n", (unsigned int)time_spent ) );
            }
            else
            {
                WPRINT_APP_INFO( ( "Read: '%s' SHA-1 Failure (", current_name ) );
                dump_bytes((uint8_t*)sha1_hash, SHA1_LENGTH );
                WPRINT_APP_INFO( ( ")\n" ) );
                WPRINT_APP_INFO( ( "Expected : " ) );
                dump_bytes((uint8_t*)expected_sha1_hash, SHA1_LENGTH );
                WPRINT_APP_INFO( ( "\n" ) );
                return ERR_UNKNOWN;
            }
        }
    }
#endif /* SHA1SUM_READ_TEST */

#ifdef SHA1SUM_WRITE_TEST
    char full_current_name[MAX_PATH_LEN];

    status = wiced_filesystem_dir_open( filesystem_handle, &dir_handle, "/read" );
    CHECK_FS_VALIDATION(status);

    /* Start write test */
    while ( status == WICED_SUCCESS )
    {
        status = wiced_filesystem_dir_read( &dir_handle, current_name, MAX_PATH_LEN, &entry_type, &finfo );
        if ( status == WICED_SUCCESS && entry_type == WICED_FILESYSTEM_FILE )
        {
            if ( get_expected_sha1sum( current_name, (uint8_t *)expected_sha1_hash, (char *)sha1_expect_list ) != 0 )
            {
                WPRINT_APP_INFO( ( "Read: '%s' not found in %s\n", current_name, SHA1_EXPECTED_LIST_FILE_NAME ) );
                return ERR_UNKNOWN;
            }

            memset(full_current_name, 0, MAX_PATH_LEN);
            sprintf(full_current_name, "/write/%s", current_name);

            if ( write_file( filesystem_handle, current_name, full_current_name, LOCAL_BUFFER_SIZE, NULL, NULL ) != ERR_CMD_OK )
            {
                WPRINT_APP_INFO( ( "write file '%s' fail\n", full_current_name ) );
                return ERR_UNKNOWN;
            }

            sw_calc_file_sha1( filesystem_handle, full_current_name, (uint8_t *)sha1_hash, &time_spent );

            if (memcmp(sha1_hash, expected_sha1_hash, SHA1_LENGTH) == 0)
            {
                WPRINT_APP_INFO( ( "Write: '%s' SHA-1 Success (", full_current_name ) );
                dump_bytes((uint8_t*)sha1_hash, SHA1_LENGTH );
                WPRINT_APP_INFO( ( ") %u ms\n", (unsigned int)time_spent ) );
            }
            else
            {
                WPRINT_APP_INFO( ( "Write: '%s' SHA-1 Failure (", full_current_name ) );
                dump_bytes((uint8_t*)sha1_hash, SHA1_LENGTH );
                WPRINT_APP_INFO( ( ")\n" ) );
                WPRINT_APP_INFO( ( "Expected : " ) );
                dump_bytes((uint8_t*)expected_sha1_hash, SHA1_LENGTH );
                WPRINT_APP_INFO( ( "\n" ) );
                return ERR_UNKNOWN;
            }
        }
    }
#endif /* SHA1SUM_WRITE_TEST */


#if (SHA1_EXPECTED_LIST_READ_FROM_FILE == 1)
    free(sha1_expect_list);
#endif
    return ERR_CMD_OK;
}

int sw_calc_sha1 (int argc, char* argv[])
{
    char* disk_name = argc >= 2 ? argv[1] : USB_DISK_STORAGE_MOUNT_NAME;
    char* file_name = argv[2];
    wiced_time_t time_spent;
    uint8_t hash_value[SHA1_LENGTH];

    wiced_filesystem_t* filesystem_handle = wiced_filesystem_retrieve_mounted_fs_handle( disk_name );

    if ( sw_calc_file_sha1( filesystem_handle, file_name, hash_value, &time_spent ) == 0 )
    {
        WPRINT_APP_INFO( ( "\nSHA-1 of '%s' =\n", file_name ) );
        dump_bytes( hash_value, SHA1_LENGTH );
        WPRINT_APP_INFO( ( "\n" ) );
        WPRINT_APP_INFO( ( "Time for SHA-1 hash feed and peek for '%s' = %u ms\n", file_name, (unsigned int)time_spent ) );
    }
    return ERR_CMD_OK;
}

/* File compare by checking sha1sum */
static int file_compare( wiced_filesystem_t* filesystem_handle, char* file1_name, char* file2_name )
{
    uint8_t hash1_value[SHA1_LENGTH] = {0}, hash2_value[SHA1_LENGTH] = {0};
    wiced_time_t time_spent;
    sw_calc_file_sha1( filesystem_handle, file1_name, hash1_value, &time_spent );
    sw_calc_file_sha1( filesystem_handle, file2_name, hash2_value, &time_spent );

    if (memcmp(hash1_value, hash2_value, SHA1_LENGTH) == 0)
    {
        WPRINT_APP_INFO( ( "SHA-1 Success\n" ) );
    }
    else
    {
       WPRINT_APP_INFO( ( "SHA-1 Failure\n" ) );
       return ERR_UNKNOWN;
    }

    return ERR_CMD_OK;
}

static void dump_bytes(const uint8_t* bptr, uint32_t len)
{
    int i = 0;

    for (i = 0; i < len; )
    {
        WPRINT_APP_INFO( ( "%02x", bptr[i++] ) );
    }
}

static int get_expected_sha1sum ( char* expect_file_name, uint8_t sha1_expect_result[SHA1_LENGTH], char* sha1_expect_list )
{
    int i, file_count;

    char sha1_hash_c[SHA1_LENGTH * 2] = {0}, sha1_hash_temp[3];
    char file_name[MAX_BYTE_PER_LINE] = {0};
    char* sha1_expect_ptr = sha1_expect_list;

    file_count = 0;
    do
    {
        memset(file_name, 0, MAX_BYTE_PER_LINE);
        memset(sha1_hash_c, 0, SHA1_LENGTH * 2);

        sscanf(sha1_expect_ptr, "%s *%s", (char*)sha1_hash_c, file_name );

#if 0
        /* Translate to upper case */
        i = 0;
        while (file_name[i])
        {
            if ( file_name[i] >= 'a' && file_name[i] <= 'z' )
            {
                file_name[i] = file_name[i] - 'a' + 'A';
            }
            i++;
        }
#endif

        //printf("SHA1 of '%s' = \n", file_name);
        //memdump((uint8_t*)sha1_hash_c, 40 );
        //printf("shift %d bytes\n", (SHA1_LENGTH * 2 + strlen(file_name) + 3));

        sha1_expect_ptr = sha1_expect_ptr + (SHA1_LENGTH * 2 + strlen(file_name) + 3);
        file_count++;
    }while ( memcmp(expect_file_name, file_name, strlen(expect_file_name)) != 0 && file_count <= MAX_SHA1_LIST_ITEM_COUNT );

    if ( file_count > MAX_SHA1_LIST_ITEM_COUNT )
    {
        /* expect_file_name is not found */
        return ERR_UNKNOWN;
    }

    /* Translate sha1sum from characters to integers */
    for ( i = 0; i < SHA1_LENGTH; i++ )
    {
        sha1_hash_temp[0] = sha1_hash_c[i*2+0];
        sha1_hash_temp[1] = sha1_hash_c[i*2+1];
        sha1_hash_temp[2] = '\0';
        sha1_expect_result[i] = strtol(sha1_hash_temp, NULL, 16);
    }

    //printf("SHA1 of '%s' = ", file_name);
    //dump_bytes((uint8_t*)sha1_expect_result, SHA1_LENGTH );
    //printf("\n");

    return ERR_CMD_OK;
}

static int sw_calc_file_sha1 ( wiced_filesystem_t* filesystem_handle, char* file_name, uint8_t sha1_result[SHA1_LENGTH], wiced_time_t* time_spent )
{
    uint64_t data_length_read = 0;
    wiced_result_t result;

    wiced_file_t   my_source_file;

    sha1_context sha1_ctx;
    wiced_time_t start_time;
    wiced_time_t end_time;
    uint8_t hash_value[SHA1_LENGTH];

    char* local_buffer = (char*) osl_malloc_align( (uint)LOCAL_BUFFER_SIZE, (uint)PLATFORM_L1_CACHE_SHIFT );
    char* test_vector_ptr = (char*)local_buffer;

    wiced_time_get_time( &start_time );

    /* Open the source file.  */
    result = wiced_filesystem_file_open( filesystem_handle, &my_source_file, file_name, WICED_FILESYSTEM_OPEN_FOR_READ );
    CHECK_FS_VALIDATION(result);

    mbedtls_sha1_starts_ret( &sha1_ctx );
    do
    {
        /* Read the file in blocks.  */
        result = wiced_filesystem_file_read( &my_source_file, local_buffer, LOCAL_BUFFER_SIZE, &data_length_read );

        if ( data_length_read > 0 )
        {
            mbedtls_sha1_update_ret( &sha1_ctx, (unsigned char *)test_vector_ptr, data_length_read );
        }
    } while ( ( result == WICED_SUCCESS ) && (data_length_read == LOCAL_BUFFER_SIZE ) ); /* Check if end of file.  */
    mbedtls_sha1_finish_ret( &sha1_ctx, (unsigned char *)hash_value );

    free( local_buffer );

    /* Done, return to caller.  */
    result = wiced_filesystem_file_close( &my_source_file );
    CHECK_FS_VALIDATION(result);

    wiced_time_get_time( &end_time );

    if ( sha1_result != NULL )
    {
        memcpy( sha1_result, hash_value, SHA1_LENGTH );
    }

    if ( time_spent != NULL )
    {
        /* Return spent time (ms) */
        *time_spent = end_time - start_time;
    }

    return ERR_CMD_OK;
}

