package main

import(
	"fmt"
	"time"
)

func routine(n int){
	fmt.Printf("I'm goroutine %d\n", n);
}

func main(){
	for x:=0; x<5;x++{
		go routine(x)
	}
	time.Sleep(1*time.Second)
}