
MESSAGE = "Nekodayo"

show-ip:
	ip a
show-files:
	@ls -lh
show-message:
	@echo ${MESSAGE}
compile: activator
	@echo "Yey!"

task-a:
	@echo "A"
	@touch a.txt
	@make task-b

task-b: a.txt
	@echo "B"
	@touch b.txt
	@make task-c

task-c: b.txt
	@echo "C"
	@touch c.txt

clean: a.txt b.txt
	@rm a.txt b.txt c.txt
	@echo "complete!"

doit:
	@make task-a
	@make clean