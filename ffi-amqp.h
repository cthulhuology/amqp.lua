// ffi-amqp.h
//
// © 2013 David J. Goehrig
//
// Copyright (c) 2013, David J Goehrig <dave@dloh.org>
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
// following conditions are met:
//
// Redistributions of source code must retain the above copyright notice, this list of conditions and the following 
// disclaimer. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and 
// the following disclaimer in the documentation and/or other materials provided with the distribution.
//
// Neither the name of the project nor the names of its contributors may be used to endorse or promote products derived
// from this software without specific prior written permission.  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
// CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

typedef enum {
	AMQP_FIELD_KIND_BOOLEAN = 't',
	AMQP_FIELD_KIND_I8 = 'b',
	AMQP_FIELD_KIND_U8 = 'B',
	AMQP_FIELD_KIND_I16 = 's',
	AMQP_FIELD_KIND_U16 = 'u',
	AMQP_FIELD_KIND_I32 = 'I',
	AMQP_FIELD_KIND_U32 = 'i',
	AMQP_FIELD_KIND_I64 = 'l',
	AMQP_FIELD_KIND_U64 = 'L',
	AMQP_FIELD_KIND_F32 = 'f',
	AMQP_FIELD_KIND_F64 = 'd',
	AMQP_FIELD_KIND_DECIMAL = 'D',
	AMQP_FIELD_KIND_UTF8 = 'S',
	AMQP_FIELD_KIND_ARRAY = 'A',
	AMQP_FIELD_KIND_TIMESTAMP = 'T',
	AMQP_FIELD_KIND_TABLE = 'F',
	AMQP_FIELD_KIND_VOID = 'V',
	AMQP_FIELD_KIND_BYTES = 'x'
} amqp_field_value_kind_t;

typedef enum amqp_response_type_enum_ {
	AMQP_RESPONSE_NONE = 0,
	AMQP_RESPONSE_NORMAL,
	AMQP_RESPONSE_LIBRARY_EXCEPTION,
	AMQP_RESPONSE_SERVER_EXCEPTION
} amqp_response_type_enum;

typedef enum amqp_sasl_method_enum_ { 
	AMQP_SASL_METHOD_PLAIN = 0 
} amqp_sasl_method_enum;

typedef int amqp_boolean_t;
typedef uint32_t amqp_method_number_t;
typedef uint32_t amqp_flags_t;
typedef uint16_t amqp_channel_t;
typedef struct { size_t len; void* bytes; } amqp_bytes_t;
typedef struct { uint8_t decimal; uint32_t value; } amqp_decimal_t;
typedef struct { int num_entries; struct amqp_table_entry_t_ *entries; } amqp_table_t;
typedef struct { int num_entries; struct amqp_field_value_t_ *entries; } amqp_array_t;

typedef struct amqp_field_value_t_ { 
	uint8_t kind; 
	union { 
		amqp_boolean_t boolean;
		int8_t i8;
		uint8_t u8;
		int16_t i16;
		uint16_t u16;
		int32_t i32;
		uint32_t u32;
		int64_t i64;
		uint64_t u64;
		float f32;
		double f64;
		amqp_decimal_t decimal;
		amqp_bytes_t bytes;
		amqp_table_t table;
		amqp_array_t array;
	} value; 
} amqp_field_value_t;

typedef struct amqp_table_entry_t_ { amqp_bytes_t key; amqp_field_value_t value; } amqp_table_entry_t;		
typedef struct amqp_pool_blocklist_t_ { int num_blocks; void **blocklist; } amqp_pool_blocklist_t;

typedef struct amqp_pool_t_ { 
	size_t pagesize;
	amqp_pool_blocklist_t pages;
	amqp_pool_blocklist_t large_blocks;
	int next_page;
	char *alloc_block;
	size_t alloc_used;
} amqp_pool_t;

typedef struct amqp_method_t_ { amqp_method_number_t id; void *decoded; } amqp_method_t;

typedef struct amqp_frame_t_ {
	uint8_t frame_type; /* 0 means no event */
	amqp_channel_t channel;
	union {
		amqp_method_t method;
		struct {
			uint16_t class_id;
			uint64_t body_size;
			void *decoded;
			amqp_bytes_t raw;
		} properties;
		amqp_bytes_t body_fragment;
		struct {
			uint8_t transport_high;
			uint8_t transport_low;
			uint8_t protocol_version_major;
			uint8_t protocol_version_minor;
		} protocol_header;
	} payload;
} amqp_frame_t;

typedef struct amqp_rpc_reply_t_ { amqp_response_type_enum reply_type; amqp_method_t reply; int library_error; } amqp_rpc_reply_t;

typedef struct amqp_connection_state_t_ *amqp_connection_state_t;

typedef struct amqp_connection_info { char *user; char *password; char *host; char *vhost; int port; } amqp_connection_info_t;

typedef struct { 
	uint8_t version_major; 
	uint8_t version_minor; 
	amqp_table_t server_properties; 
	amqp_bytes_t mechanisms; 
	amqp_bytes_t locales;
} amqp_connection_start_t;

typedef struct {
	amqp_table_t client_properties;
	amqp_bytes_t mechanism;
	amqp_bytes_t response;
	amqp_bytes_t locale;
} amqp_connection_start_ok_t;

typedef struct {
	amqp_bytes_t challenge;
} amqp_connection_secure_t;

typedef struct {
	amqp_bytes_t response;
} amqp_connection_secure_ok_t;

typedef struct {
	uint16_t channel_max;
	uint32_t frame_max;
	uint16_t heartbeat;
} amqp_connection_tune_t;

typedef struct {
	uint16_t channel_max;
	uint32_t frame_max;
	uint16_t heartbeat;
} amqp_connection_tune_ok_t;

typedef struct {
	amqp_bytes_t virtual_host;
	amqp_bytes_t capabilities;
	amqp_boolean_t insist;
} amqp_connection_open_t;

typedef struct {
	amqp_bytes_t known_hosts;
} amqp_connection_open_ok_t;

typedef struct {
	uint16_t reply_code;
	amqp_bytes_t reply_text;
	uint16_t class_id;
	uint16_t method_id;
} amqp_connection_close_t;

typedef struct {
	char dummy;
} amqp_connection_close_ok_t;

typedef struct {
	amqp_bytes_t out_of_band;
} amqp_channel_open_t;

typedef struct {
	amqp_bytes_t channel_id;
} amqp_channel_open_ok_t;

typedef struct {
	amqp_boolean_t active;
} amqp_channel_flow_t;

typedef struct {
	amqp_boolean_t active;
} amqp_channel_flow_ok_t;

typedef struct {
	uint16_t reply_code;
	amqp_bytes_t reply_text;
	uint16_t class_id;
	uint16_t method_id;
} amqp_channel_close_t;

typedef struct {
	char dummy;
} amqp_channel_close_ok_t;

typedef struct {
	amqp_bytes_t realm;
	amqp_boolean_t exclusive;
	amqp_boolean_t passive;
	amqp_boolean_t active;
	amqp_boolean_t write;
	amqp_boolean_t read;
} amqp_access_request_t;

typedef struct {
	uint16_t ticket;
} amqp_access_request_ok_t;

typedef struct {
	uint16_t ticket;
	amqp_bytes_t exchange;
	amqp_bytes_t type;
	amqp_boolean_t passive;
	amqp_boolean_t durable;
	amqp_boolean_t auto_delete;
	amqp_boolean_t internal;
	amqp_boolean_t nowait;
	amqp_table_t arguments;
} amqp_exchange_declare_t;

typedef struct {
	char dummy;
} amqp_exchange_declare_ok_t;

typedef struct {
	uint16_t ticket;
	amqp_bytes_t exchange;
	amqp_boolean_t if_unused;
	amqp_boolean_t nowait;
} amqp_exchange_delete_t;

typedef struct {
	char dummy;
} amqp_exchange_delete_ok_t;

typedef struct {
	uint16_t ticket;
	amqp_bytes_t destination;
	amqp_bytes_t source;
	amqp_bytes_t routing_key;
	amqp_boolean_t nowait;
	amqp_table_t arguments;
} amqp_exchange_bind_t;

typedef struct {
	char dummy;
} amqp_exchange_bind_ok_t;

typedef struct {
	uint16_t ticket;
	amqp_bytes_t destination;
	amqp_bytes_t source;
	amqp_bytes_t routing_key;
	amqp_boolean_t nowait;
	amqp_table_t arguments;
} amqp_exchange_unbind_t;

typedef struct {
	char dummy;
} amqp_exchange_unbind_ok_t;

typedef struct {
	uint16_t ticket;
	amqp_bytes_t queue;
	amqp_boolean_t passive;
	amqp_boolean_t durable;
	amqp_boolean_t exclusive;
	amqp_boolean_t auto_delete;
	amqp_boolean_t nowait;
	amqp_table_t arguments;
} amqp_queue_declare_t;

typedef struct {
	amqp_bytes_t queue;
	uint32_t message_count;
	uint32_t consumer_count;
} amqp_queue_declare_ok_t;

typedef struct {
	uint16_t ticket;
	amqp_bytes_t queue;
	amqp_bytes_t exchange;
	amqp_bytes_t routing_key;
	amqp_boolean_t nowait;
	amqp_table_t arguments;
} amqp_queue_bind_t;

typedef struct {
	char dummy;
} amqp_queue_bind_ok_t;

typedef struct {
	uint16_t ticket;
	amqp_bytes_t queue;
	amqp_boolean_t nowait;
} amqp_queue_purge_t;

typedef struct {
	uint32_t message_count;
} amqp_queue_purge_ok_t;

typedef struct {
	uint16_t ticket;
	amqp_bytes_t queue;
	amqp_boolean_t if_unused;
	amqp_boolean_t if_empty;
	amqp_boolean_t nowait;
} amqp_queue_delete_t;

typedef struct {
	uint32_t message_count;
} amqp_queue_delete_ok_t;

typedef struct {
	uint16_t ticket;
	amqp_bytes_t queue;
	amqp_bytes_t exchange;
	amqp_bytes_t routing_key;
	amqp_table_t arguments;
} amqp_queue_unbind_t;

typedef struct {
	char dummy;
} amqp_queue_unbind_ok_t;

typedef struct {
	uint32_t prefetch_size;
	uint16_t prefetch_count;
	amqp_boolean_t global;
} amqp_basic_qos_t;

typedef struct {
	char dummy;	
} amqp_basic_qos_ok_t;

typedef struct {
	uint16_t ticket;
	amqp_bytes_t queue;
	amqp_bytes_t consumer_tag;
	amqp_boolean_t no_local;
	amqp_boolean_t no_ack;
	amqp_boolean_t exclusive;
	amqp_boolean_t nowait;
	amqp_table_t arguments;
} amqp_basic_consume_t;

typedef struct {
	amqp_bytes_t consumer_tag;
} amqp_basic_consume_ok_t;

typedef struct {
	amqp_bytes_t consumer_tag;
	amqp_boolean_t nowait;
} amqp_basic_cancel_t;

typedef struct {
	amqp_bytes_t consumer_tag;
} amqp_basic_cancel_ok_t;

typedef struct {
	uint16_t ticket;
	amqp_bytes_t exchange;
	amqp_bytes_t routing_key;
	amqp_boolean_t mandatory;
	amqp_boolean_t immediate;
} amqp_basic_publish_t;

typedef struct {
	uint16_t reply_code;
	amqp_bytes_t reply_text;
	amqp_bytes_t exchange;
	amqp_bytes_t routing_key;
} amqp_basic_return_t;

typedef struct {
	amqp_bytes_t consumer_tag;
	uint64_t delivery_tag;
	amqp_boolean_t redelivered;
	amqp_bytes_t exchange;
	amqp_bytes_t routing_key;
} amqp_basic_deliver_t;

typedef struct {
	uint16_t ticket;
	amqp_bytes_t queue;
	amqp_boolean_t no_ack;
} amqp_basic_get_t;

typedef struct {
	uint64_t delivery_tag;
	amqp_boolean_t redelivered;
	amqp_bytes_t exchange;
	amqp_bytes_t routing_key;
	uint32_t message_count;
} amqp_basic_get_ok_t;

typedef struct {
	amqp_bytes_t cluster_id;
} amqp_basic_get_empty_t;

typedef struct {
	uint64_t delivery_tag;
	amqp_boolean_t multiple;
} amqp_basic_ack_t;

typedef struct {
	uint64_t delivery_tag;
	amqp_boolean_t requeue;
} amqp_basic_reject_t;

typedef struct {
	amqp_boolean_t requeue;
} amqp_basic_recover_async_t;

typedef struct {
	amqp_boolean_t requeue;
} amqp_basic_recover_t;

typedef struct {
	char dummy;
} amqp_basic_recover_ok_t;

typedef struct {
	uint64_t delivery_tag;
	amqp_boolean_t multiple;
	amqp_boolean_t requeue;
} amqp_basic_nack_t;

typedef struct {
	char dummy;
} amqp_tx_select_t;

typedef struct {
	char dummy;
} amqp_tx_select_ok_t;

typedef struct {
	char dummy;
} amqp_tx_commit_t;

typedef struct {
	char dummy;
} amqp_tx_commit_ok_t;

typedef struct {
	char dummy;
} amqp_tx_rollback_t;

typedef struct {
	char dummy;
} amqp_tx_rollback_ok_t;

typedef struct {
	amqp_boolean_t nowait;
} amqp_confirm_select_t;

typedef struct {
	char dummy;
} amqp_confirm_select_ok_t;

typedef struct {
	amqp_flags_t _flags;
	char dummy;
} amqp_connection_properties_t;

typedef struct {
	amqp_flags_t _flags;
	char dummy;
} amqp_channel_properties_t;

typedef struct {
	amqp_flags_t _flags;
	char dummy;
} amqp_access_properties_t;

typedef struct {
	amqp_flags_t _flags;
	char dummy;
} amqp_exchange_properties_t;

typedef struct {
	amqp_flags_t _flags;
	char dummy;
} amqp_queue_properties_t;

typedef struct amqp_basic_properties_t_ {
	amqp_flags_t _flags;
	amqp_bytes_t content_type;
	amqp_bytes_t content_encoding;
	amqp_table_t headers;
	uint8_t delivery_mode;
	uint8_t priority;
	amqp_bytes_t correlation_id;
	amqp_bytes_t reply_to;
	amqp_bytes_t expiration;
	amqp_bytes_t message_id;
	uint64_t timestamp;
	amqp_bytes_t user_id;
	amqp_bytes_t app_id;
	amqp_bytes_t cluster_id;
} amqp_basic_properties_t;

typedef struct {
	amqp_flags_t _flags;
	char dummy;
} amqp_tx_properties_t;

typedef struct {
	amqp_flags_t _flags;
	char dummy;
} amqp_confirm_properties_t;

// AMQP methods

char const * amqp_version(void);
void init_amqp_pool(amqp_pool_t* pool, size_t pagesize);
void recycle_amqp_pool(amqp_pool_t* pool);
void empty_amqp_pool(amqp_pool_t* pool);
void* amqp_pool_alloc(amqp_pool_t* pool, size_t ammount);
void amqp_pool_alloc_bytes(amqp_pool_t *pool, size_t amount, amqp_bytes_t *output);
amqp_bytes_t amqp_cstring_bytes(char const* cstr);
amqp_bytes_t amqp_bytes_malloc_dup(amqp_bytes_t src);
amqp_bytes_t amqp_bytes_malloc(size_t ammount);
void amqp_bytes_free(amqp_bytes_t bytes);
amqp_connection_state_t amqp_new_connection(void);
int amqp_get_sockfd(amqp_connection_state_t state);
void amqp_set_sockfd(amqp_connection_state_t state, int sockfd);
int amqp_tune_connection(amqp_connection_state_t state, int channel_max, int frame_max, int heartbeat);
int amqp_get_channel_max(amqp_connection_state_t state);
int amqp_destroy_connection(amqp_connection_state_t state);
int amqp_handle_input(amqp_connection_state_t state, amqp_bytes_t received_data, amqp_frame_t *decoded_frame);
amqp_boolean_t amqp_release_buffers_ok(amqp_connection_state_t state);
void amqp_release_buffers(amqp_connection_state_t state);
void amqp_maybe_release_buffers(amqp_connection_state_t state);
int amqp_send_frame(amqp_connection_state_t state, amqp_frame_t const *frame);
int amqp_table_entry_cmp(void const *entry1, void const *entry2);
int amqp_open_socket(char const *hostname, int portnumber);
int amqp_send_header(amqp_connection_state_t state);
amqp_boolean_t amqp_frames_enqueued(amqp_connection_state_t state);
int amqp_simple_wait_frame(amqp_connection_state_t state, amqp_frame_t *decoded_frame);
int amqp_simple_wait_method(amqp_connection_state_t state, amqp_channel_t expected_channel, amqp_method_number_t expected_method, amqp_method_t *output);
int amqp_send_method(amqp_connection_state_t state, amqp_channel_t channel, amqp_method_number_t id, void *decoded);
amqp_rpc_reply_t amqp_simple_rpc(amqp_connection_state_t state, amqp_channel_t channel, amqp_method_number_t request_id, amqp_method_number_t *expected_reply_ids, void *decoded_request_method);
void * amqp_simple_rpc_decoded(amqp_connection_state_t state, amqp_channel_t channel, amqp_method_number_t request_id, amqp_method_number_t reply_id, void *decoded_request_method);
amqp_rpc_reply_t amqp_get_rpc_reply(amqp_connection_state_t state);
amqp_rpc_reply_t amqp_login(amqp_connection_state_t state, char const *vhost, int channel_max, int frame_max, int heartbeat, amqp_sasl_method_enum sasl_method,char const *username, char const *password);
int amqp_basic_publish(amqp_connection_state_t state, amqp_channel_t channel, amqp_bytes_t exchange, amqp_bytes_t routing_key, amqp_boolean_t mandatory, amqp_boolean_t immediate, struct amqp_basic_properties_t_ const *properties, amqp_bytes_t body);
amqp_rpc_reply_t amqp_channel_close(amqp_connection_state_t state, amqp_channel_t channel, int code);
amqp_rpc_reply_t amqp_connection_close(amqp_connection_state_t state, int code);
int amqp_basic_ack(amqp_connection_state_t state, amqp_channel_t channel, uint64_t delivery_tag, amqp_boolean_t multiple);
amqp_rpc_reply_t amqp_basic_get(amqp_connection_state_t state, amqp_channel_t channel, amqp_bytes_t queue, amqp_boolean_t no_ack);
int amqp_basic_reject(amqp_connection_state_t state, amqp_channel_t channel, uint64_t delivery_tag, amqp_boolean_t requeue);
amqp_boolean_t amqp_data_in_buffer(amqp_connection_state_t state);
char * amqp_error_string(int err);
int amqp_decode_table(amqp_bytes_t encoded, amqp_pool_t *pool, amqp_table_t *output, size_t *offset);
int amqp_encode_table(amqp_bytes_t encoded, amqp_table_t *input, size_t *offset);
void amqp_default_connection_info(struct amqp_connection_info *parsed);
int amqp_parse_url(char *url, struct amqp_connection_info *parsed);
char const * amqp_constant_name(int constantNumber);
amqp_boolean_t amqp_constant_is_hard_error(int constantNumber);
char const * amqp_method_name(amqp_method_number_t methodNumber);
amqp_boolean_t amqp_method_has_content(amqp_method_number_t methodNumber);
int amqp_decode_method(amqp_method_number_t methodNumber, amqp_pool_t *pool, amqp_bytes_t encoded, void **decoded);
int amqp_decode_properties(uint16_t class_id, amqp_pool_t *pool, amqp_bytes_t encoded, void **decoded);
int amqp_encode_method(amqp_method_number_t methodNumber, void *decoded, amqp_bytes_t encoded);
int amqp_encode_properties(uint16_t class_id, void *decoded, amqp_bytes_t encoded);
amqp_channel_open_ok_t * amqp_channel_open(amqp_connection_state_t state, amqp_channel_t channel);
amqp_channel_flow_ok_t * amqp_channel_flow(amqp_connection_state_t state, amqp_channel_t channel, amqp_boolean_t active);
amqp_exchange_declare_ok_t * amqp_exchange_declare(amqp_connection_state_t state, amqp_channel_t channel, amqp_bytes_t exchange, amqp_bytes_t type, amqp_boolean_t passive, amqp_boolean_t durable, amqp_table_t arguments);
amqp_exchange_delete_ok_t * amqp_exchange_delete(amqp_connection_state_t state, amqp_channel_t channel, amqp_bytes_t exchange, amqp_boolean_t if_unused);
amqp_exchange_bind_ok_t * amqp_exchange_bind(amqp_connection_state_t state, amqp_channel_t channel, amqp_bytes_t destination, amqp_bytes_t source, amqp_bytes_t routing_key, amqp_table_t arguments);
amqp_exchange_unbind_ok_t * amqp_exchange_unbind(amqp_connection_state_t state, amqp_channel_t channel, amqp_bytes_t destination, amqp_bytes_t source, amqp_bytes_t routing_key, amqp_table_t arguments);
amqp_queue_declare_ok_t * amqp_queue_declare(amqp_connection_state_t state, amqp_channel_t channel, amqp_bytes_t queue, amqp_boolean_t passive, amqp_boolean_t durable, amqp_boolean_t exclusive, amqp_boolean_t auto_delete, amqp_table_t arguments);
amqp_queue_bind_ok_t * amqp_queue_bind(amqp_connection_state_t state, amqp_channel_t channel, amqp_bytes_t queue, amqp_bytes_t exchange, amqp_bytes_t routing_key, amqp_table_t arguments);
amqp_queue_purge_ok_t * amqp_queue_purge(amqp_connection_state_t state, amqp_channel_t channel, amqp_bytes_t queue);
amqp_queue_delete_ok_t * amqp_queue_delete(amqp_connection_state_t state, amqp_channel_t channel, amqp_bytes_t queue, amqp_boolean_t if_unused, amqp_boolean_t if_empty);
amqp_queue_unbind_ok_t * amqp_queue_unbind(amqp_connection_state_t state, amqp_channel_t channel, amqp_bytes_t queue, amqp_bytes_t exchange, amqp_bytes_t routing_key, amqp_table_t arguments);
amqp_basic_qos_ok_t * amqp_basic_qos(amqp_connection_state_t state, amqp_channel_t channel, uint32_t prefetch_size, uint16_t prefetch_count, amqp_boolean_t global);
amqp_basic_consume_ok_t * amqp_basic_consume(amqp_connection_state_t state, amqp_channel_t channel, amqp_bytes_t queue, amqp_bytes_t consumer_tag, amqp_boolean_t no_local, amqp_boolean_t no_ack, amqp_boolean_t exclusive, amqp_table_t arguments);
amqp_basic_cancel_ok_t * amqp_basic_cancel(amqp_connection_state_t state, amqp_channel_t channel, amqp_bytes_t consumer_tag);
amqp_basic_recover_ok_t * amqp_basic_recover(amqp_connection_state_t state, amqp_channel_t channel, amqp_boolean_t requeue);
amqp_tx_select_ok_t * amqp_tx_select(amqp_connection_state_t state, amqp_channel_t channel);
amqp_tx_commit_ok_t * amqp_tx_commit(amqp_connection_state_t state, amqp_channel_t channel);
amqp_tx_rollback_ok_t * amqp_tx_rollback(amqp_connection_state_t state, amqp_channel_t channel);
amqp_confirm_select_ok_t * amqp_confirm_select(amqp_connection_state_t state, amqp_channel_t channel);
