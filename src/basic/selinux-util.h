/* SPDX-License-Identifier: LGPL-2.1+ */
#pragma once

#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "macro.h"
#include "label.h"

bool mac_selinux_use(void);
void mac_selinux_retest(void);

int mac_selinux_init(void);
void mac_selinux_finish(void);
void mac_selinux_reload(void);

int mac_selinux_fix(const char *path, LabelFixFlags flags);
#if 0 /// UNNEEDED by elogind
int mac_selinux_apply(const char *path, const char *label);

int mac_selinux_get_create_label_from_exe(const char *exe, char **label);
int mac_selinux_get_our_label(char **label);
int mac_selinux_get_child_mls_label(int socket_fd, const char *exe, const char *exec_label, char **label);
#endif // 0
char* mac_selinux_free(char *label);

int mac_selinux_create_file_prepare(const char *path, mode_t mode);
int mac_selinux_create_file_prepare_at(int dirfd, const char *path, mode_t mode);
void mac_selinux_create_file_clear(void);
#if 0 /// UNNEEDED by elogind

int mac_selinux_create_socket_prepare(const char *label);
void mac_selinux_create_socket_clear(void);

int mac_selinux_bind(int fd, const struct sockaddr *addr, socklen_t addrlen);
#endif // 0

DEFINE_TRIVIAL_CLEANUP_FUNC(char*, mac_selinux_free);
