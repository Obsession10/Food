# TCP/IP SERVER-CLIENT SOCKET PROGRAMMING 
   Statement : Implement a concurrent TCP server to which maximum N clients can connect . From T to T seconds ,the server will receive a message from the clients who will be consider the number of a food ( 1 to 5) chosen randomly by that customer . 
   The server will count requests and for the most preferred type of food ( the one with the most requests on that round) will send to the requesting clients as an answer : "The meal is served". The other clients ( who have hosen a different type) will respond with 
"Unavailable" . 
   A customer who was served with lunch will display a "Village!" and he will finish his execution. A declined customer will still try a randomly selected request after a randomly chosen range (up to 60 seconds). At three declined requests, a customer will display "Swap the canteen! I'm starving here!" and he will finish his execution. 
