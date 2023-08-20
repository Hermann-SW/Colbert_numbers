
demo: validate
	@echo
	time -f %E\\n  gp -q < validate.gp
	time -f %E\\n  ./validate
	time -f %E\\n  python validate.py

lint: validate.cc Colbert.h
	cpplint --filter=-legal/copyright $<
	cppcheck --enable=all --suppress=missingIncludeSystem $< --check-config
	pylint validate.py

validate: validate.cc Colbert.h
	g++ validate.cc -lgmp -lgmpxx -O3 -Wall -pedantic -Wextra -o validate

Colbert.h: Colbert.py
	sed "s/C =//;\
	     y/[]/{}/;\
	     s/\([0-9a-fx][0-9a-fx]*\)/mpz_class\(\"\1\"\)/g;" $< > $@

clean:
	rm -rf validate Colbert.h __pycache__
