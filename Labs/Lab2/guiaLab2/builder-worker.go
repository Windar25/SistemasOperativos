package main

import (
	"fmt"
	"sync"
)

var (
	buffer [5]int = [5]int{-1, -1, -1, -1, -1}
	index  int
	wg1    sync.WaitGroup
	wg2    sync.WaitGroup
	wg     sync.WaitGroup
	lock1  sync.Mutex
	lock2  sync.Mutex
	ch1    = make(chan int)
	ch2    = make(chan int)
	empty  = 5 //cuenta el número de slots vacíos
	full   = 0 //cuenta el número de slots llenos
	mutex  = 1
)

/*func down(value int){
	var lock sync.Mutex
	lock.Lock()
	if value > 0 {
		value --
	}else if value == 0{
		<-ch1
	}
	lock.Unlock()
}

func up(value int){
	var lock sync.Mutex
	lock.Lock()
	value ++
	if cap(ch1) == 0 {
		ch1<-1
		value--
	}
	lock.Unlock()
}*/

// Si el productor llena el buffer, debe bloquearse hasta que el consumidor consuma algo
func productor() {
	for n := 0; n < 20; n++ {
		item := n * n
		wg1.Wait()
		<-ch1
		//fmt.Printf("LLegue productor\n")
		if full == 5 {
			wg1.Add(1)
			<-ch1
			wg1.Wait()
			<-ch1
		} else if full == 0 && empty != 5 {
			wg2.Done()
		}
		empty--
		full++
		index = n % 5
		buffer[index] = item
		fmt.Printf("productor %d %d %v\n", index, item, buffer)
		ch1 <- 1
	}
	wg.Done()
}

// Casos a considerar:
// Si el consumidor no tiene espacios donde consumir, debe detenerse hasta que el producto produzca algo

func consumidor() {
	var item int
	for n := 0; n < 20; n++ {
		//fmt.Printf("LLegue consumidor\n")
		wg2.Wait()

		<-ch1
		if full == 0 {
			wg2.Add(1)
			ch1 <- 1
			wg2.Wait()
			<-ch1
		} else if full == 5 && empty != 0 {
			wg1.Done()
		}
		empty++
		full--
		index = n % 5
		item = buffer[index]
		buffer[index] = -1
		fmt.Printf("consumidor %d %d %v\n", index, item, buffer)
		ch1 <- 1
	}
	wg.Done()
}

func main() {
	wg1.Add(0)
	wg2.Add(0)
	go consumidor()
	go productor()
	ch1 <- 1
	var input string
	fmt.Scanln(&input)
}
