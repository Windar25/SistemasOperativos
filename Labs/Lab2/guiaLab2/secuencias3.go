package main

import(
	"fmt"
	"sync"
	"os"
)

var (
	w sync.WaitGroup
	count = 0
	ch1 = make (chan int)
	ch2 = make (chan int)
	ch3 = make (chan int)
	ch4 = make (chan int)
	ch5 = make (chan int)
)

func routineA(){
	for{
		<-ch1
		fmt.Printf("A")
		ch2<-1
	}
}


func routineB(){
	for{
		<-ch1
		fmt.Printf("B")
		ch2<-1
	}
}


func routineC(){
	for{
		<-ch2
		fmt.Printf("C")
		ch3<-1
	}
}


func routineD(){
	for{
		<-ch3
		fmt.Printf("D")
		ch4<-1
	}
}


func routineE(){
	for{
		<-ch4
		fmt.Printf("E")
		
		//ch2<-1
		//ch4<-1
		count++
		if count == 20 {
			fmt.Printf("\n")
			os.Exit(1)
		}
		ch1<-1
	}
}

/*func manageSelects(){
	select{
		case <-ch3: 
			ch4<-1
		case <-ch1: 
			ch2<-1
		default:
			manageSelects()
	}
	ch5<-1
	<-ch8
	count ++
	if count == 50 {
		os.Exit(1)
	}
}*/

/*func manageSignals(){
	for{
		select{
			case <-ch3: 
				ch4<-1
				ch5<-1
				<-ch8
			case <-ch1: 
				ch2<-1
				ch5<-1
				<-ch8
	}
	count ++
		if count == 50 {
			os.Exit(1)
		}
	}	
}*/

func main(){
	go routineE()
	go routineD()
	go routineC()
	go routineB()
	go routineA()
	ch1<-1
	var input string
	fmt.Scanln(&input)
}