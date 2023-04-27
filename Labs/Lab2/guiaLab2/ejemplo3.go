package main

import(
	"fmt"
)

/*
	cha := make(chan int) 	// se crea un canal con valores enteros
	ch <- x					// se envía un valor que contiene la variable x al canal ch
	x = <- ch 				// se recibe del canal un valor y lo asigna a la variable x
	<-ch					// se recibe del canal un valor, el mismo que es descartado					
	close(ch)				// coloca internamente una bandera indicando que no se enviarán más valores en un canal
*/


func main(){
	naturals := make(chan int)
	squares := make(chan int)

	// Counter
	go func(){
		for x:=0; x<20 ; x++{
			naturals<-x
		}
		close(naturals)
	}()

	// Squarer 
	go func(){
		for x:= range naturals{
			squares <- x * x
		}
		close(squares)
	}()

	// Printer
	for x:= range squares{
		fmt.Println(x)
	}
}