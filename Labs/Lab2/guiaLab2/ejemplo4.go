package main

import "fmt"

func main(){
	//También se puede declarar como
	//done := make(chan struct{})
	done := make(chan struct{})
	for x:= 0; x < 5;x++{
		go func(count int){
			fmt.Printf("I'm goroutine %d\n",count)
			//junto a done <- 1
			done <- struct{}{}
		}(x)
	}
	for x:= 0 ; x<5; x++{
		<-done
		fmt.Println("Se ha liberado una subrutina")
	}
	fmt.Println("Ha terminado el programa")
}