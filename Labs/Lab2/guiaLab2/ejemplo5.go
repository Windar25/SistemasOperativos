package main

import "fmt"

/*
	ch = make(chan string, 3)	//declaracion de canales con buffer
	ch <- "A" 					// se envia una variable	



*/

func main(){
	ch := make(chan string, 4)

	ch<-"A"
	ch<-"B"
	ch<-"C"
	ch<- "D"
	fmt.Println(<- ch) // “A”

	//cap te da la capacidad del canal
	fmt.Println(cap(ch)) // “3”
	fmt.Println(<- ch) // “B”
	fmt.Println(<- ch) // “C”

	//usamos la instrucción select
	/*
	Un select espera hasta que alguna comunicación para algún caso se encuentre listo para proceder.
	Luego realiza esas comunicaciones y ejecuta las instrucciones asociadas al caso; las otras
	comunicaciones no suceden. Un select sin casos, slect{}, espera por siempre
	*/
	//y:= "5"
	ch1 := make(chan string, 1)
	ch2 := make(chan string, 2)
	//ch3 := make(chan string, 3)
	//la función select solo se ejecuta una vez
	select{
		case <- ch1:
			//
		case x:= <- ch2:
			fmt.Println(x)
			//
		//case ch3 <- y:
			//
		default:
			fmt.Println("Caso default en select")
	}
	//un select sin casos espera por siempre
	//select{}
	// si multiples casos están listos se elige uno al azar
	/*
	Algunas veces se desea tratar de enviar o recibir sobre un canal pero evitando bloquearse si el canal
	no está listo (una comunicación no bloqueante). Una instrucción select también puede hacer eso.
	Un select puede tener un default, la cual especifica que hacer cuando ninguna de las
	comunicaciones puede proceder inmediatamente.
	*/
	ch<- "E"
	ch<- "F"
	ch<- "G"
	for i:= 0; i< 4; i++{
		<-ch
	}
	select{
     	case <-ch:
     		<-ch
     	default:
     		fmt.Println("El canal está vacío y no se ha bloqueado por la función select")
	}

}