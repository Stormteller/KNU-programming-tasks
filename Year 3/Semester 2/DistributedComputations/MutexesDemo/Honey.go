package main

import (
	"fmt"
	"time"
	"sync"
)

var MAX_HONEY = 10
var wg = sync.WaitGroup{}
var potMutex = &sync.Mutex{}

func bear(honeypotInput <- chan bool) {
	for {
		<-honeypotInput
		fmt.Println("Bear awoke. Honey eaten.")
	}
}

func honeypot(putHoneyChan <- chan int, getUpBear chan bool) {
	var honey = 0
	for {
		var toadd = <-putHoneyChan
		honey = honey + toadd
		if (honey == MAX_HONEY) {
			getUpBear <- true
			honey = 0
		}
	}
}

func bee(putHoney chan int) {
	for {
		time.Sleep(1000 * time.Millisecond)
		potMutex.Lock()
		putHoney <- 1
		potMutex.Unlock()
		fmt.Println("Bee put honey")

	}
}

func main() {
	var putHoneyChan = make(chan int, 5)
	//var beeDoneChan = make(chan bool)
	var bearChan = make(chan bool)

	wg.Add(3)
	go honeypot(putHoneyChan, bearChan)
	go bear(bearChan)
	go bee(putHoneyChan)
	go bee(putHoneyChan)
	go bee(putHoneyChan)
	wg.Wait()
	//for {
	//	<- beeDoneChan
	//	go bee(putHoneyChan, beeDoneChan)
	//}
}
