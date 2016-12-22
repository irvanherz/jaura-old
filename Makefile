.PHONY: clean All

All:
	@echo "----------Building project:[ Jaura - Release ]----------"
	@"$(MAKE)" -f  "Jaura.mk" PreBuild && "$(MAKE)" -f  "Jaura.mk"
clean:
	@echo "----------Cleaning project:[ Jaura - Release ]----------"
	@"$(MAKE)" -f  "Jaura.mk" clean
