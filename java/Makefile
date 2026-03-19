PYTHON = python3 -B
MAIN = main.py
SOURCE_FILES = main.py data.py hora.py compromisso.py aula.py evento.py reuniao.py orientacao.py pessoal.py lista.py
OUTPUT_FILES = relatconfirmados.txt relatadiados.txt relatcancelados.txt relatcompromissos.txt resultado.txt

all: run

run:
	@PYTHONDONTWRITEBYTECODE=1 $(PYTHON) $(MAIN)

clean:
	@rm -f $(OUTPUT_FILES)
	@rm -rf __pycache__
	@find . -name "*.pyc" -delete
	@find . -name "__pycache__" -type d -exec rm -rf {} + 2>/dev/null || true

.PHONY: all run clean test help check