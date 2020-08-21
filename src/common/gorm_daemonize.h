#ifndef _GORM_DAEMONIZE_H__
#define _GORM_DAEMONIZE_H__
#ifndef _WIN32
#include "gorm_define.h"
#include "gorm_log.h"
#include "gorm_error.h"
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int
GORM_Daemonize()
{
    int status;
    pid_t pid, sid;
    int fd;

    pid = fork();
    switch (pid) {
    case -1:
        GORM_STDERR("fork() failed: %s", strerror(errno));
        return GORM_ERROR;

    case 0:
        break;

    default:
        /* parent terminates */
        exit(0);
    }

    /* 1st child continues and becomes the session leader */

    sid = setsid();
    if (sid < 0) {
        GORM_STDERR("setsid() failed: %s", strerror(errno));
        return GORM_ERROR;
    }

    umask(0);

    /* redirect stdin, stdout and stderr to "/dev/null" */

    fd = open("/dev/null", O_RDWR);
    if (fd < 0) {
        GORM_STDERR("open(\"/dev/null\") failed: %s", strerror(errno));
        return GORM_ERROR;
    }

    status = dup2(fd, STDIN_FILENO);
    if (status < 0) {
        GORM_STDERR("dup2(%d, STDIN) failed: %s", fd, strerror(errno));
        close(fd);
        return GORM_ERROR;
    }

    status = dup2(fd, STDOUT_FILENO);
    if (status < 0) {
        GORM_STDERR("dup2(%d, STDOUT) failed: %s", fd, strerror(errno));
        close(fd);
        return GORM_ERROR;
    }

    status = dup2(fd, STDERR_FILENO);
    if (status < 0) {
        GORM_STDERR("dup2(%d, STDERR) failed: %s", fd, strerror(errno));
        close(fd);
        return GORM_ERROR;
    }

    if (fd > STDERR_FILENO) {
        status = close(fd);
        if (status < 0) {
            GORM_STDERR("close(%d) failed: %s", fd, strerror(errno));
            return GORM_ERROR;
        }
    }

    return GORM_OK;
}

#endif
#endif

