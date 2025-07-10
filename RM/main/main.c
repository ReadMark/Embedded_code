#include <stdio.h>
#include <stdbool.h>
#include <sys/unistd.h>
#include <unistd.h> //  POSIX 운영 체제 API에 대한 접근을 제공하는 파일
#include "driver/uart.h" // 통신용 드라이버 인터페이스 정의
#include "esp_log.h" // 로그 메시지 사용
#include "hal/uart_types.h"
#include <stdint.h> // 정확한 크기의 정수형 타입들을 정의
#include "driver/gpio.h"

#define BUF_SIZE 1024
#define LED 2

void app_main(void) {
	
	uart_config_t uart_config = {
		.baud_rate = 115200, // 통신 속도
		.data_bits = UART_DATA_8_BITS, // 데이터 비트
 		.parity = UART_PARITY_DISABLE, // 패리티 없음
		.stop_bits = UART_STOP_BITS_1, // 정지 비트 1개
		.flow_ctrl = UART_HW_FLOWCTRL_DISABLE, // 하드웨어 흐름 제어 비활성
	};
	

	
	uart_param_config(UART_NUM_0, &uart_config); // 포트 번호, 매개 변수 설정
	uart_driver_install(UART_NUM_0, BUF_SIZE * 2, 0, 0, NULL, 0);
	// 포트 번호, RX 버퍼 크기, TX버퍼 (만약 0이라면 TX를 사용하지 않음), UART 큐 이벤트 깊이, 큐 핸들로 성공시 큐 핸들 작성 (만약 NULL이라먄 이벤트 큐를 사용하지 않음), 인터럽트 할당 플래그
	
	uint8_t data[BUF_SIZE + 1];
    while(1) {
		int len = uart_read_bytes(UART_NUM_0, data, BUF_SIZE, 100 / portTICK_PERIOD_MS);
		// timeOut ROTS tick 수	
		if (len > 0) {
			data[len] = '\0';
			printf("input : %s\n", (char *)data);
		}
	}
}
