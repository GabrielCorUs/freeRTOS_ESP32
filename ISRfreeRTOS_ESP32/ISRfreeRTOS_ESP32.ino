
#include <freertos/FreeRTOS.h> //incluimos las librerias que se utilizaran 
#include <freertos/task.h>


int LED_PIN = 27;             //Declaramos los pines del boton y el led
int PUSH_BUTTON_PIN = 33;

TaskHandle_t ISR = NULL;      // declaramos una variable tipo TaskHandle_t nombrada ISR que sea igual a NULL

void IRAM_ATTR button_isr_handler(){  // creamos una funcion tipo void en la memoria interna llamada button_isr_handler con una funcion dentro
  xTaskResumeFromISR(ISR);
}

void interrupt_task(void *arg){       //La tarea está en un bucle infinito y se suspende a sí misma hasta que se produce una interrupción de botón. 
                                       // Cuando se reanuda, cambia el estado del LED y envía un mensaje por el puerto serie.
  bool led_status = false;
  while(1){
    vTaskSuspend(NULL);
    led_status = !led_status;
    digitalWrite(LED_PIN, led_status);
    printf("Button pressed!\n");
  }
}

void setup(){         //

  pinMode(PUSH_BUTTON_PIN, INPUT_PULLUP); // Configuramos el pin push boton como entrada y lo configuramos en modo pull up
  pinMode(LED_PIN ,OUTPUT);               // Configuramos el pin del led como entrada


  attachInterrupt(PUSH_BUTTON_PIN, button_isr_handler, FALLING);   // configuramos la interrupcion en el boton

  xTaskCreate(interrupt_task, "interrupt_task", 4096, NULL, 10, &ISR);  // Finalmente, se crea la tarea interrupt_task utilizando la función xTaskCreate().
}

void loop(){
  // No es necesario implementar nada aquí
}
