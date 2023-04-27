package main

import(
	"fmt"
)

var j = 1


func fibonacci (n int, c chan int){
	x,y := 0,1
	for i:= 0 ; i < 2*n ; i++ {
		fmt.Printf("Voy a guardar en el canal : EJECUCION %d\n",j)
		c <- x

		fmt.Printf("Orden: %v - Valor:%v\n",i,x)
		x,y=y,x+y
		j++
	}
	close(c)
}

func main(){
	c := make(chan int, 20)
	fmt.Println(cap(c))
	go fibonacci(cap(c),c)
	for i := range c{
		fmt.Printf("Voy a leer en el canal : EJECUCION %d\n",j)
		fmt.Println(i)
		j++
	}
}