package main

import(
	"fmt"
	"sync"
)

func routine(n int){
	defer wg.Done()
	fmt.Printf("Im goroutine %d\n",n)
}

var wg sync.WaitGroup

func main(){
	for x:= 0 ; x<5 ; x++ {
		wg.Add(1)
		go routine(x)
	}
	wg.Wait()
	fmt.Println("Salida de función main")
}