from os import system

SIG_CONT = 25

if __name__ == "__main__":
	pid = input("Enter pid: ")
	kill_string = "kill -CONT -" + str(pid)
	print kill_string
	system(kill_string)
	
