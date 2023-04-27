package main

import(
	"fmt"
	"sync"
)

var {
	wg sync.WaitGroup
	ch1 chan struct{} = make(chan struct{},1)
	ch2 chan struct{} = make(chan struct{},1)
	ch3 chan struct{} = make(chan struct{},1)
}
//los chan struct pueden funcionar como una interrupción
func worker1(){
	fmt.Printf("Sistemas ")
	wg.Done()
}

func worker2(){
	fmt.Printf("INF239 ")
	wg.Done()
	ch1 <- struct{}
}

func worker3(){
	fmt.Printf("Operativos ")
	wg.Done()
}

func worker4(){
	fmt.Printf("\n ")
	wg.Done()
}

func main(){
	wg.Add(4)
	go worker1()
	go worker2()
	go worker3()
	go worker4()
	wg.Wait()
}

//Solución Alejandro Bello/Viktor Klevnikhov