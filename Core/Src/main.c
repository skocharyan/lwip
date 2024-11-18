/* USER CODE BEGIN Header */
/**
 *******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 *******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "lwip.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "mdns.h"
#include "lwip/apps/httpd.h"
#include "lwip/netif.h"
#include "lwip/dhcp.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
void ip_change_callback(struct netif *netif);
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
struct netif gentif;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void StartDHCP(void);
void StartMDNS(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
err_t httpd_post_receive_data(void *connection, struct pbuf *p) {
    if (p != NULL) {
        printf("Received POST data: %.*s\n", p->len, (char *)p->payload);
    }
    return ERR_OK;
}

void httpd_post_finished(void *connection, char *response_uri, u16_t response_uri_len) {
    printf("POST processing finished for URI: %s\n", response_uri);
}

err_t httpd_post_begin(void *connection, const char *uri, const char *http_request,
                       u16_t http_request_len, int content_len, char *response_uri, u16_t response_uri_len, u8_t *post_data) {
    printf("POST request started for URI: %s\n", uri);
    return ERR_OK;
}

void httpd_cgi_handler(struct fs_file *file, const char* uri, int iNumParams,
                       char **pcParam, char **pcValue) {
    __NOP();
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_LWIP_Init();

    /* Configure network interface with DHCP */
    netif_add(&gentif, IP_ADDR_ANY, IP_ADDR_ANY, IP_ADDR_ANY, NULL, &ethernetif_init, &ethernet_input);
    netif_set_status_callback(&gentif, ip_change_callback);
    netif_set_default(&gentif);
    netif_set_up(&gentif);

    /* Start DHCP */
    StartDHCP();

    /* Main loop */
    while (1) {
        MX_LWIP_Process();

        /* Check for DHCP success and start mDNS */
        if (dhcp_supplied_address(&gentif)) {
            StartMDNS();
            break;
        }
    }

    /* Start HTTP server */
    httpd_init();

    /* Main loop */
    while (1) {
        MX_LWIP_Process();
    }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
     */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 4;
    RCC_OscInitStruct.PLL.PLLN = 168;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

/* Start DHCP */
void StartDHCP(void) {
    dhcp_start(&gentif);
    printf("DHCP started, waiting for IP address...\n");
}

/* Start mDNS */
void StartMDNS(void) {
    if (dhcp_supplied_address(&gentif)) {
        mdns_resp_add_netif(&gentif, "mydevice", 60); // Replace "mydevice" with your desired hostname
        mdns_resp_add_service(&gentif, "My HTTP Server", "_http", DNSSD_PROTO_TCP, 80, 60, NULL, NULL);
        printf("mDNS initialized with hostname: mydevice\n");
    }
}

void ip_change_callback(struct netif *netif) {
    if (netif_is_up(netif) && dhcp_supplied_address(netif)) {
        printf("IP Address changed: %s\n", ip4addr_ntoa(netif_ip4_addr(netif)));
        StartMDNS();
    }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void) {
    __disable_irq();
    while (1) {
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line) {
}
#endif /* USE_FULL_ASSERT */
