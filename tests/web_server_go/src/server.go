package main

import (
	"fmt"
	"html"
	"log"
	"net/http"
)

func main() {
	http.HandleFunc("/", func (w http.ResponseWriter, r *http.Request)  {
		fmt.Fprintf(w, "Hello %s", html.EscapeString(r.URL.Path[1:]))
		fmt.Printf("Served %q\n", html.EscapeString(r.URL.Path))
	})

	http.HandleFunc("/hello", func (w http.ResponseWriter, r *http.Request)  {
		fmt.Fprintf(w, "Hello")
		fmt.Printf("Served %q\n", html.EscapeString(r.URL.Path))
	})

	fmt.Printf("Starting server...\n")
	if err := http.ListenAndServe(":8000", nil); err != nil {
		log.Fatal(err)
	}
}