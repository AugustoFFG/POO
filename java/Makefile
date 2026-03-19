JAVAC = javac
JAVA = java
SRC = $(wildcard *.java)
CLASSES = $(SRC:.java=.class)
MAIN_CLASS = Main

all: compile

compile: $(SRC)
	$(JAVAC) *.java

run: compile
	@if [ -f "agenda.txt" ] && [ -f "posicoes.txt" ]; then \
		$(JAVA) $(MAIN_CLASS); \
	else \
		echo "Erro: Arquivos de entrada não encontrados!"; \
		echo "Certifique-se de que agenda.txt e posicoes.txt estão no diretório atual"; \
	fi

clean:
	rm -f *.class
	rm -f relatconfirmados.txt relatadiados.txt relatcancelados.txt relatcompromissos.txt resultado.txt

.PHONY: all compile run test clean clean-all help