
OBJDIR:=obj
CC:= g++ -g -Werror -Wall -DNDEBUG -pedantic-errors --std=c++11
OBJS:= $(addprefix $(OBJDIR)/, cacheSim.o Cache.o Simulator.o);

cacheSim: $(OBJS)
	$(CC) -o $@ $^

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CC) -c $< -o $@

.PHONY: test
test:
	@sed -i 's/testsFolder=.*/testsFolder=.\/tests\//' run.sh
	@echo 'Running tests 1'
	@bash run.sh
	@sed -i 's/testsFolder=.*/testsFolder=.\/tests2\//' run.sh
	@echo 'Running tests 2'
	@bash run.sh
	@echo 'Done'

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o
	rm -f cacheSim
