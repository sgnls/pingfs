/*
 * Copyright (c) 2013-2015 Erik Ekman <yarrick@kryo.se>
 *
 * Permission to use, copy, modify, and/or distribute this software for any purpose
 * with or without fee is hereby granted, provided that the above copyright notice
 * and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */
#ifndef __CHUNK_H__
#define __CHUNK_H__
#include <stdint.h>
#include <sys/socket.h>

#define CHUNK_SIZE 1024

struct host;

struct chunk {
	/* Link for list of all active chunks */
	struct chunk *next_active;
	/* Link for list of chunks in this same file */
	struct chunk *next_file;
	struct host *host;
	uint16_t id;
	uint16_t seqno;
	uint16_t len;
};

/* Allocate chunk and give it id and seqno */
struct chunk *chunk_create();

void chunk_free(struct chunk *c);

/* Add/remove chunk from active list */
void chunk_add(struct chunk *c);
void chunk_remove(struct chunk *c);

/* Handle icmp reply */
void chunk_reply(void *userdata, struct sockaddr_storage *addr,
	size_t addrlen, uint16_t id, uint16_t seqno, const uint8_t *data, size_t len);
#endif
