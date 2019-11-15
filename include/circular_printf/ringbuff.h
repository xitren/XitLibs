/**
 * Author:          Tilen MAJERLE <tilen@majerle.eu>
 */
#ifndef RINGBUFF_HDR_H
#define RINGBUFF_HDR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdint.h>

	/**
	 * \brief           Buffer structure
	 */
	typedef struct {
		uint8_t* buff; /*!< Pointer to buffer data.
                                                    Buffer is considered initialized when `buff != NULL` and `size` */
		size_t size; /*!< Size of buffer data. Size of actual buffer is `1` byte less than value holds */
		size_t r; /*!< Next read pointer. Buffer is considered empty when `r == w` and full when `w == r - 1` */
		size_t w; /*!< Next write pointer. Buffer is considered empty when `r == w` and full when `w == r - 1` */
	} circular_buff_t;

	uint8_t circular_buff_init(circular_buff_t* buff, void* buffdata, size_t size);
	void circular_buff_free(circular_buff_t* buff);
	void circular_buff_reset(circular_buff_t* buff);

	/* Read/Write functions */
	size_t circular_buff_write(circular_buff_t* buff, const void* data, size_t btw);
	size_t circular_buff_read(circular_buff_t* buff, void* data, size_t btr);
	size_t circular_buff_peek(circular_buff_t* buff, size_t skip_count, void* data, size_t btp);

	/* Buffer size information */
	size_t circular_buff_get_free(circular_buff_t* buff);
	size_t circular_buff_get_full(circular_buff_t* buff);

	/* Read data block management */
	void * circular_buff_get_linear_block_read_address(circular_buff_t* buff);
	size_t circular_buff_get_linear_block_read_length(circular_buff_t* buff);
	size_t circular_buff_skip(circular_buff_t* buff, size_t len);

	/* Write data block management */
	void * circular_buff_get_linear_block_write_address(circular_buff_t* buff);
	size_t circular_buff_get_linear_block_write_length(circular_buff_t* buff);
	size_t circular_buff_advance(circular_buff_t* buff, size_t len);

#undef BUF_PREF         /* Prefix not needed anymore */

	/**
	 * \}
	 */

#ifdef __cplusplus
}
#endif

#endif /* RINGBUFF_HDR_H */


