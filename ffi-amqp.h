typedef int amqp_boolean_t;
typedef uint32_t amqp_method_number_t;
typedef uint32_t amqp_flags_t;
typedef uint16_t amqp_channel_t;

typedef struct { size_t len; void* bytes; } amqp_bytes_t;
typedef struct { uint8_t decimal; uint32_t value; } amqp_decimal_t;
typedef struct { int num_entries; struct amqp_table_entry_t_ *entries; } amqp_table_t;
typedef struct { int num_entries; struct amqp_field_value_t_ *entries; } amqp_array_t;

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

typedef enum amqp_response_type_enum_ {
	AMQP_RESPONSE_NONE = 0,
	AMQP_RESPONSE_NORMAL,
	AMQP_RESPONSE_LIBRARY_EXCEPTION,
	AMQP_RESPONSE_SERVER_EXCEPTION
} amqp_response_type_enum;

typedef struct amqp_rpc_reply_t_ { amqp_response_type_enum reply_type; amqp_method_t reply; int library_error; } amqp_rpc_reply_t;

typedef struct amqp_connection_state_t_ *amqp_connection_state_t;
typedef enum amqp_sasl_method_enum_ { AMQP_SASL_METHOD_PLAIN = 0 } amqp_sasl_method_enum;

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
 

