package main

import (
	"sync"
	"time"
	"fmt"
	"math/rand"
)

var toHairdresser = make(chan int)

var hairdresserMutex = &sync.Mutex{}

var seed = rand.NewSource(time.Now().UnixNano());

var random = rand.New(seed);

func runHairdresser() {
	for {
		var client int = <- toHairdresser
		hairdresserMutex.Lock()
		fmt.Println("Hairdresser started work with client ", client)
		time.Sleep(1000 * time.Millisecond)
		hairdresserMutex.Unlock()
		fmt.Println("Hairdresser done work with client ", client)
	}

}

func main() {
	var i = 0
	go runHairdresser()
	for {
		var sleepTime = time.Duration(random.Intn(5000) + 500)
		time.Sleep(sleepTime)
		toHairdresser <- i
		i++
	}
}
