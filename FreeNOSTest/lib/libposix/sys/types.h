#pragma once
#include "Types.h"


/** Used for process IDs and process group IDs. */
typedef ProcessID pid_t;

/** Used for sizes of objects. */
typedef Size size_t;

/** Used for a count of bytes or an error indication. */
typedef slong ssize_t;

/** Used for device IDs. */
typedef DeviceID dev_t;

/** Used for file serial numbers. */
typedef uint ino_t;

/** Used for some file attributes. */
typedef uint mode_t;

/** Used for user IDs. */
typedef u16 uid_t;

/** Used for group IDs. */
typedef u16 gid_t;

/** Used for link counts. */
typedef Size nlink_t;

/** Used for file sizes. */
typedef sint off_t;

/** Used for file block counts. */
typedef sint blkcnt_t;

/** Used for block sizes. */
typedef sint blksize_t;

/** Used for time in seconds. */
typedef u64 time_t;

/**
* @}
*/