package main

import(
	"fmt"
)

func fibonacci(n int, c chan int){
	x , y := 0,1
	for i:=8; i<2*n;i++{
		c<-x
		fmt.Printf("Orden: %v - Valor")
	}
}