package main

import "fmt"

func sum(s []int, c chan int){
	sum:= 0
	for _, v:= range s{
		sum+=v
	}
	c <- sum //send sum to c
}

func main(){
	s := []int{7,2,8,-9,4,0}

	c := make(chan int)
	go sum(s[:len(s)/2],c)
	go sum(s[len(s)/2:],c)
	x , y := <- c, <- c //receive from c

	fmt.Println(x,y,x+y)
	//una forma de crear una espera es usando channels
	//el hilo que queremos que demore, le ponemos una lectura
	//donde no recibirá nada hasta que la otra función le envíe un mensaje
	// si la primera función quiere leer y no hay nada, esta se bloquea
}
