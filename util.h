/* Scumm Tools
 * Copyright (C) 2002-2006 The ScummVM project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#ifndef UTIL_H
#define UTIL_H

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#if !defined(_MSC_VER)
#include <unistd.h>
#endif

#ifdef WIN32
#include <io.h>
#include <process.h>
#endif


/*
 * Some useful types
 */

typedef unsigned char byte;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef signed char int8;
typedef signed short int16;
typedef signed int int32;


/*
 * Various utility macros
 */

#if defined(_MSC_VER)

	#define scumm_stricmp stricmp
	#define scumm_strnicmp _strnicmp
	#define snprintf _snprintf

	#define SCUMM_LITTLE_ENDIAN
	#pragma once
	#pragma warning( disable : 4068 ) /* turn off "unknown pragma" warning */
	#pragma warning( disable : 4996 ) /* turn off warnings about unsafe functions */

#elif defined(__MINGW32__)

	#define scumm_stricmp stricmp
	#define scumm_strnicmp strnicmp

	#define SCUMM_LITTLE_ENDIAN

#elif defined(UNIX)

	#define scumm_stricmp strcasecmp
	#define scumm_strnicmp strncasecmp

	#if defined(__DECCXX) /* Assume alpha architecture */
	#define INVERSE_MKID
	#define SCUMM_NEED_ALIGNMENT
	#endif

#else

	#error No system type defined

#endif


/*
 * GCC specific stuff
 */
#if defined(__GNUC__)
        #define GCC_PACK __attribute__((packed))
        #define NORETURN __attribute__((__noreturn__))
        #define GCC_PRINTF(x,y) __attribute__((format(printf, x, y)))
#else
        #define GCC_PACK
        #define GCC_PRINTF(x,y)
#endif

#define ARRAYSIZE(x) ((int)(sizeof(x) / sizeof(x[0])))

static inline uint32 SWAP_32(uint32 a) {
	return ((a >> 24) & 0xFF) | ((a >> 8) & 0xFF00) | ((a << 8) & 0xFF0000) |
		((a << 24) & 0xFF000000);
}

static inline uint16 SWAP_16(uint16 a) {
	return ((a >> 8) & 0xFF) | ((a << 8) & 0xFF00);
}

#define FORCEINLINE static inline

FORCEINLINE uint16 READ_LE_UINT16(const void *ptr) {
	const byte *b = (const byte *)ptr;
	return (b[1] << 8) + b[0];
}
FORCEINLINE uint32 READ_LE_UINT32(const void *ptr) {
	const byte *b = (const byte *)ptr;
	return (b[3] << 24) + (b[2] << 16) + (b[1] << 8) + (b[0]);
}
FORCEINLINE void WRITE_LE_UINT16(void *ptr, uint16 value) {
	byte *b = (byte *)ptr;
	b[0] = (byte)(value >> 0);
	b[1] = (byte)(value >> 8);
}
FORCEINLINE void WRITE_LE_UINT32(void *ptr, uint32 value) {
	byte *b = (byte *)ptr;
	b[0] = (byte)(value >>  0);
	b[1] = (byte)(value >>  8);
	b[2] = (byte)(value >> 16);
	b[3] = (byte)(value >> 24);
}

FORCEINLINE uint16 READ_BE_UINT16(const void *ptr) {
	const byte *b = (const byte *)ptr;
	return (b[0] << 8) + b[1];
}
FORCEINLINE uint32 READ_BE_UINT32(const void *ptr) {
	const byte *b = (const byte*)ptr;
	return (b[0] << 24) + (b[1] << 16) + (b[2] << 8) + (b[3]);
}
FORCEINLINE void WRITE_BE_UINT16(void *ptr, uint16 value) {
	byte *b = (byte *)ptr;
	b[0] = (byte)(value >> 8);
	b[1] = (byte)(value >> 0);
}
FORCEINLINE void WRITE_BE_UINT32(void *ptr, uint32 value) {
	byte *b = (byte *)ptr;
	b[0] = (byte)(value >> 24);
	b[1] = (byte)(value >> 16);
	b[2] = (byte)(value >>  8);
	b[3] = (byte)(value >>  0);
}

#if defined(__GNUC__)
#define NORETURN_PRE
#define NORETURN_POST	__attribute__((__noreturn__))
#elif defined(_MSC_VER)
#define NORETURN_PRE	_declspec(noreturn)
#define NORETURN_POST
#else
#define NORETURN_PRE
#define NORETURN_POST
#endif


/* File I/O */
uint8 readByte(FILE *fp);
uint16 readUint16BE(FILE *fp);
uint16 readUint16LE(FILE *fp);
uint32 readUint32BE(FILE *fp);
uint32 readUint32LE(FILE *fp);
void writeByte(FILE *fp, uint8 b);
void writeUint16BE(FILE *fp, uint16 value);
void writeUint16LE(FILE *fp, uint16 value);
void writeUint32BE(FILE *fp, uint32 value);
void writeUint32LE(FILE *fp, uint32 value);
uint32 fileSize(FILE *fp);

/* Misc stuff */
void NORETURN_PRE error(const char *s, ...) NORETURN_POST;
void warning(const char *s, ...);
void debug(int level, const char *s, ...);
void notice(const char *s, ...);
void getPath(const char *fullpath, char *path);
void getFilename(const char *fullpath, char *filename);

#endif
