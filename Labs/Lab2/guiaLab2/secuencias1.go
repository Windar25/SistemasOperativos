package main

import(
	"fmt"
	"sync"
	"os"
)

var (
	w sync.WaitGroup
	ch  = make (chan byte)
	ch1 = make (chan int, 1)
	ch2 = make (chan int, 1)
	ch3 = make (chan int, 1)
	ch4 = make (chan int, 1)
	ch5 = make (chan int, 1)
	count = 0
)

func routineA(){
	//defer 	w.Done()
	for{
		fmt.Printf("A")
		ch1<-1
		<-ch5
	}
}


func routineB(){
	//defer 	w.Done()
	for{
		<-ch1
		fmt.Printf("B")
		ch2<-1
	}
}


func routineC(){
	//defer 	w.Done()
	for{
		<-ch2
		fmt.Printf("C")
		ch3<-1
	}
}


func routineD(){
	//defer 	w.Done()
	for{
		<-ch3
		fmt.Printf("D")
		ch4<-1
	}
}


func routineE(){
	//defer 	w.Done()
	for{
		<-ch4
		fmt.Printf("E")
		count++
		ch5<-1
		if count==10 {
			os.Exit(1)
		}
	}
}

func main(){
	go routineE()
	go routineD()
	go routineC()
	go routineB()
	go routineA()
	var input string;
	fmt.Scanln(&input)
	
}