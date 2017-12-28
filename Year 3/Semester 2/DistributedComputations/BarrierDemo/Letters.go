package main

import (
	"fmt"
	"sync"
	"math/rand"
	"time"
)

var seed = rand.NewSource(time.Now().UnixNano());

var random = rand.New(seed);

func change_letter(str *[]byte) {
	var ind = random.Intn(len(*str))
	switch (*str)[ind] {
	case 'A':
		(*str)[ind] = 'C'
		break
	case 'B':
		(*str)[ind] = 'D'
		break
	case 'C':
		(*str)[ind] = 'A'
		break
	case 'D':
		(*str)[ind] = 'B'
		break
	}
}

func worker(init_str *[]byte, wg *sync.WaitGroup, finish chan bool, again chan bool) {
	for {
		change_letter(init_str)
		wg.Done()
		select {
		case <-finish:
			return
		case <-again:
			continue
		}
	}
}

func calc_A_and_B_amount(str []byte) int {
	var res = 0
	for i := 0; i < len(str); i++ {
		if str[i] == 'A' || str[i] == 'B' {
			res++
		}
	}
	return res
}

func checker(strings *[][]byte, wg *sync.WaitGroup, finish chan bool, again chan bool) {
	for {
		wg.Wait()
		var calcDict = make(map[int]int)
		for i := 0; i < len(*strings); i++ {
			if _, ok := calcDict[calc_A_and_B_amount((*strings)[i])]; ok {
				calcDict[calc_A_and_B_amount((*strings)[i])] += 1
			} else {
				calcDict[calc_A_and_B_amount((*strings)[i])] = 1
			}
		}
		for _, v := range calcDict {
			if v >= 3 {
				for i := 0; i < len(*strings); i++ {
					finish <- true
				}
				fmt.Println("DONE")
				fmt.Println(strings)
				return
			}
		}
		fmt.Println("Barrier restarted")
		fmt.Println(strings)
		wg.Add(len(*strings))
		for i := 0; i < len(*strings); i++ {
			again <- true
		}
	}
}

func main() {
	var wg = &sync.WaitGroup{}
	var finish = make(chan bool)
	var again = make(chan bool)
	wg.Add(4)
	var strs = [][]byte {[]byte("AABB"), []byte("CCDD"), []byte("CCBB"), []byte("AADD")};
	go worker(&strs[0], wg, finish, again)
	go worker(&strs[1], wg, finish, again)
	go worker(&strs[2], wg, finish, again)
	go worker(&strs[3], wg, finish, again)
	checker(&strs, wg, finish, again)
}
