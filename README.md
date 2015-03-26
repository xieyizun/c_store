The codes are for the task1 task2 and task3 of C_store project.

Go to the current directory and type make

then you can do many operations:
./db load orders
you will load the orders.tbl
./db retrieve orders
then you can input several orderkey that you want to query
./db compress orders 1
you will sort and compress the custkey in the orders
./db load customer
you will load the customer.tbl
./db join
you will join the customer table and the order table to see each order belong to which customer
./db count
you will how many records there are in the order table

"orders.tbl" must be put in this directory
"customer.tbl" must be put in this directory
