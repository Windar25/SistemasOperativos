package main

import(
	"fmt"
	"sync"
)

var(
	wgH sync.WaitGroup
	wgO sync.WaitGroup
	wgCL sync.WaitGroup
	lock = 0
)

func routineH(){
	for{
		wgH.Wait()
		fmt.Printf("H")
		if lock == 0 {
			lock++
		}else{
			wgH.Add(1)
			lock=0
			wgO.Done()
		}
	}
}

func routineO(){
	for{
		wgO.Wait()
		fmt.Printf("O")
		wgO.Add(1)
		wgCL.Done()
	}

}

func routineCambioLinea(){
	for{
		wgCL.Wait()
		fmt.Printf("\n")
		wgCL.Add(1)
		wgH.Done()
	}
}

func main(){
	wgO.Add(1)
	wgCL.Add(1)
	go routineH()
	go routineO()
	go routineCambioLinea()
	var input string
	fmt.Scanln(&input)
}