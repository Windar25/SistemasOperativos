package main

import(
	"fmt"
	"sync"
	//"os"
)

var (
	w sync.WaitGroup
	count = 0
	ch1 chan struct{} = make (chan struct{})
	ch2 chan struct{} = make (chan struct{})
	ch3 chan struct{} = make (chan struct{})
	ch4 chan struct{} = make (chan struct{})
	ch5 chan struct{} = make (chan struct{})

)

func routineA(){
	for{
		<-ch1
		fmt.Printf("A")
		/*if count == 50{
			os.Exit(1)
		}*/
		ch2<-struct{}{}
	}
}


func routineB(){
	for{
		<-ch1
		fmt.Printf("B")
		ch2<-struct{}{}
	}
}


func routineC(){
	for{
		<-ch2
		fmt.Printf("C")
		ch3<-struct{}{}
	}
}


func routineD(){
	for{
		<-ch3
		fmt.Printf("D")
		ch4<-struct{}{}
	}
}


func routineE(){
	for{
		<-ch4
		fmt.Printf("E")
		ch1<-struct{}{}
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

func main(){
	go routineE()
	go routineD()
	go routineC()
	go routineB()
	go routineA()

	ch1<-struct{}{}
	var input string
	fmt.Scanln(&input)
}

//Con ayuda de Ricardo Bartra