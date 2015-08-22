

UML_PATH=uml
PLANTUML_BIN=java -jar ../lib/plantuml/plantuml.jar

%.png : %.pu
	$(PLANTUML_BIN) $<

UML_SOURCES = $(wildcard $(UML_PATH)/*.pu)
UML_PNGS = $(patsubst %.pu,%.png,$(UML_SOURCES))

all_docs: $(UML_PNGS)
	doxygen

all: all_docs


