#include <freertos/FreeRTOS.h>//Incluimos las librerias que se utilizaran
#include <freertos/task.h>

TaskHandle_t myTaskHandle = NULL; //Declaramos 2 variable stipo TaskHandle con valor NULL
TaskHandle_t myTaskHandle2 = NULL;

void Demo_Task(void *arg)      // Creamos 2 funciones 
{
    while (1) {                                   //Se crea un bucle while que se ejecutará continuamente mientras la tarea esté activa.
        Serial.println("Demo_Task printing..");   //Se imprime "Demo_Task printing.."
        vTaskDelay(pdMS_TO_TICKS(1000));          //vTaskDelay se utiliza para pausar la tarea durante un período de tiempo específico
    }                                             //La funcion pdMS_TO_TICKS se utiliza para convertir el valor de microsegundos a Ticks
}

void Demo_Task2(void *arg)
{
    while (1) {
        Serial.println("Demo_Task2 printing..");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void setup()   //  se están creando dos tareas 
               // utilizando la función "xTaskCreate" y "xTaskCreatePinnedToCore", que son funciones proporcionadas por FreeRTOS para crear tareas.
          
{
    Serial.begin(115200);
    xTaskCreate(Demo_Task, "Demo_Task", 4096, NULL, 10, &myTaskHandle);
    xTaskCreatePinnedToCore(Demo_Task2, "Demo_Task2", 4096, NULL, 10, &myTaskHandle2, 1);
}

void loop() // La funcion void loop la dejamos vacias
{
}
