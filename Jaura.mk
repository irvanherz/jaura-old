##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=Jaura
ConfigurationName      :=Release
WorkspacePath          := "/media/irvan/DATA/Jaura"
ProjectPath            := "/media/irvan/DATA/Jaura"
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Irvan
Date                   :=20/12/16
CodeLitePath           :="/home/irvan/.codelite"
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="Jaura.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -Tldscript -nostdlib -m32
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -O2 -Wall $(Preprocessors)
CFLAGS   :=  -Wall -masm=intel -m32 -nostdlib -nostartfiles -ffreestanding --no-leading-underscore $(Preprocessors)
ASFLAGS  := -32
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/KInit.c$(ObjectSuffix) $(IntermediateDirectory)/KInitMultiboot.S$(ObjectSuffix) $(IntermediateDirectory)/KInitMultiboot2.c$(ObjectSuffix) $(IntermediateDirectory)/KinitDescriptor.c$(ObjectSuffix) $(IntermediateDirectory)/KInitMemory.c$(ObjectSuffix) $(IntermediateDirectory)/KInitMm.c$(ObjectSuffix) $(IntermediateDirectory)/KMain.c$(ObjectSuffix) $(IntermediateDirectory)/KVmm.c$(ObjectSuffix) $(IntermediateDirectory)/KScreen.c$(ObjectSuffix) $(IntermediateDirectory)/KLib.c$(ObjectSuffix) \
	$(IntermediateDirectory)/KHeap.c$(ObjectSuffix) $(IntermediateDirectory)/KPmm.c$(ObjectSuffix) $(IntermediateDirectory)/KMmHelper.c$(ObjectSuffix) $(IntermediateDirectory)/KFrame.c$(ObjectSuffix) $(IntermediateDirectory)/DList.c$(ObjectSuffix) $(IntermediateDirectory)/SList.c$(ObjectSuffix) $(IntermediateDirectory)/KMalloc.c$(ObjectSuffix) $(IntermediateDirectory)/Device.c$(ObjectSuffix) $(IntermediateDirectory)/ATA.c$(ObjectSuffix) $(IntermediateDirectory)/PIT.c$(ObjectSuffix) \
	$(IntermediateDirectory)/PIC.c$(ObjectSuffix) $(IntermediateDirectory)/Tmpfs.c$(ObjectSuffix) $(IntermediateDirectory)/KFilesystem.c$(ObjectSuffix) $(IntermediateDirectory)/Fnode.c$(ObjectSuffix) $(IntermediateDirectory)/File.c$(ObjectSuffix) $(IntermediateDirectory)/FAT16.c$(ObjectSuffix) $(IntermediateDirectory)/Interrupt.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Release || $(MakeDirCommand) ./Release


$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:
	@echo Executing Pre Build commands ...
	
	@echo Done


##
## Objects
##
$(IntermediateDirectory)/KInit.c$(ObjectSuffix): KInit.c $(IntermediateDirectory)/KInit.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/irvan/DATA/Jaura/KInit.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/KInit.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/KInit.c$(DependSuffix): KInit.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/KInit.c$(ObjectSuffix) -MF$(IntermediateDirectory)/KInit.c$(DependSuffix) -MM "KInit.c"

$(IntermediateDirectory)/KInit.c$(PreprocessSuffix): KInit.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/KInit.c$(PreprocessSuffix) "KInit.c"

$(IntermediateDirectory)/KInitMultiboot.S$(ObjectSuffix): KInitMultiboot.S $(IntermediateDirectory)/KInitMultiboot.S$(DependSuffix)
	$(AS) "/media/irvan/DATA/Jaura/KInitMultiboot.S" $(ASFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/KInitMultiboot.S$(ObjectSuffix) -I$(IncludePath)
$(IntermediateDirectory)/KInitMultiboot.S$(DependSuffix): KInitMultiboot.S
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/KInitMultiboot.S$(ObjectSuffix) -MF$(IntermediateDirectory)/KInitMultiboot.S$(DependSuffix) -MM "KInitMultiboot.S"

$(IntermediateDirectory)/KInitMultiboot.S$(PreprocessSuffix): KInitMultiboot.S
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/KInitMultiboot.S$(PreprocessSuffix) "KInitMultiboot.S"

$(IntermediateDirectory)/KInitMultiboot2.c$(ObjectSuffix): KInitMultiboot2.c $(IntermediateDirectory)/KInitMultiboot2.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/irvan/DATA/Jaura/KInitMultiboot2.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/KInitMultiboot2.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/KInitMultiboot2.c$(DependSuffix): KInitMultiboot2.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/KInitMultiboot2.c$(ObjectSuffix) -MF$(IntermediateDirectory)/KInitMultiboot2.c$(DependSuffix) -MM "KInitMultiboot2.c"

$(IntermediateDirectory)/KInitMultiboot2.c$(PreprocessSuffix): KInitMultiboot2.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/KInitMultiboot2.c$(PreprocessSuffix) "KInitMultiboot2.c"

$(IntermediateDirectory)/KinitDescriptor.c$(ObjectSuffix): KinitDescriptor.c $(IntermediateDirectory)/KinitDescriptor.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/irvan/DATA/Jaura/KinitDescriptor.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/KinitDescriptor.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/KinitDescriptor.c$(DependSuffix): KinitDescriptor.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/KinitDescriptor.c$(ObjectSuffix) -MF$(IntermediateDirectory)/KinitDescriptor.c$(DependSuffix) -MM "KinitDescriptor.c"

$(IntermediateDirectory)/KinitDescriptor.c$(PreprocessSuffix): KinitDescriptor.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/KinitDescriptor.c$(PreprocessSuffix) "KinitDescriptor.c"

$(IntermediateDirectory)/KInitMemory.c$(ObjectSuffix): KInitMemory.c $(IntermediateDirectory)/KInitMemory.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/irvan/DATA/Jaura/KInitMemory.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/KInitMemory.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/KInitMemory.c$(DependSuffix): KInitMemory.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/KInitMemory.c$(ObjectSuffix) -MF$(IntermediateDirectory)/KInitMemory.c$(DependSuffix) -MM "KInitMemory.c"

$(IntermediateDirectory)/KInitMemory.c$(PreprocessSuffix): KInitMemory.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/KInitMemory.c$(PreprocessSuffix) "KInitMemory.c"

$(IntermediateDirectory)/KInitMm.c$(ObjectSuffix): KInitMm.c $(IntermediateDirectory)/KInitMm.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/irvan/DATA/Jaura/KInitMm.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/KInitMm.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/KInitMm.c$(DependSuffix): KInitMm.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/KInitMm.c$(ObjectSuffix) -MF$(IntermediateDirectory)/KInitMm.c$(DependSuffix) -MM "KInitMm.c"

$(IntermediateDirectory)/KInitMm.c$(PreprocessSuffix): KInitMm.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/KInitMm.c$(PreprocessSuffix) "KInitMm.c"

$(IntermediateDirectory)/KMain.c$(ObjectSuffix): KMain.c $(IntermediateDirectory)/KMain.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/irvan/DATA/Jaura/KMain.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/KMain.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/KMain.c$(DependSuffix): KMain.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/KMain.c$(ObjectSuffix) -MF$(IntermediateDirectory)/KMain.c$(DependSuffix) -MM "KMain.c"

$(IntermediateDirectory)/KMain.c$(PreprocessSuffix): KMain.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/KMain.c$(PreprocessSuffix) "KMain.c"

$(IntermediateDirectory)/KVmm.c$(ObjectSuffix): KVmm.c $(IntermediateDirectory)/KVmm.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/irvan/DATA/Jaura/KVmm.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/KVmm.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/KVmm.c$(DependSuffix): KVmm.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/KVmm.c$(ObjectSuffix) -MF$(IntermediateDirectory)/KVmm.c$(DependSuffix) -MM "KVmm.c"

$(IntermediateDirectory)/KVmm.c$(PreprocessSuffix): KVmm.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/KVmm.c$(PreprocessSuffix) "KVmm.c"

$(IntermediateDirectory)/KScreen.c$(ObjectSuffix): KScreen.c $(IntermediateDirectory)/KScreen.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/irvan/DATA/Jaura/KScreen.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/KScreen.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/KScreen.c$(DependSuffix): KScreen.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/KScreen.c$(ObjectSuffix) -MF$(IntermediateDirectory)/KScreen.c$(DependSuffix) -MM "KScreen.c"

$(IntermediateDirectory)/KScreen.c$(PreprocessSuffix): KScreen.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/KScreen.c$(PreprocessSuffix) "KScreen.c"

$(IntermediateDirectory)/KLib.c$(ObjectSuffix): KLib.c $(IntermediateDirectory)/KLib.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/irvan/DATA/Jaura/KLib.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/KLib.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/KLib.c$(DependSuffix): KLib.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/KLib.c$(ObjectSuffix) -MF$(IntermediateDirectory)/KLib.c$(DependSuffix) -MM "KLib.c"

$(IntermediateDirectory)/KLib.c$(PreprocessSuffix): KLib.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/KLib.c$(PreprocessSuffix) "KLib.c"

$(IntermediateDirectory)/KHeap.c$(ObjectSuffix): KHeap.c $(IntermediateDirectory)/KHeap.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/irvan/DATA/Jaura/KHeap.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/KHeap.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/KHeap.c$(DependSuffix): KHeap.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/KHeap.c$(ObjectSuffix) -MF$(IntermediateDirectory)/KHeap.c$(DependSuffix) -MM "KHeap.c"

$(IntermediateDirectory)/KHeap.c$(PreprocessSuffix): KHeap.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/KHeap.c$(PreprocessSuffix) "KHeap.c"

$(IntermediateDirectory)/KPmm.c$(ObjectSuffix): KPmm.c $(IntermediateDirectory)/KPmm.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/irvan/DATA/Jaura/KPmm.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/KPmm.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/KPmm.c$(DependSuffix): KPmm.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/KPmm.c$(ObjectSuffix) -MF$(IntermediateDirectory)/KPmm.c$(DependSuffix) -MM "KPmm.c"

$(IntermediateDirectory)/KPmm.c$(PreprocessSuffix): KPmm.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/KPmm.c$(PreprocessSuffix) "KPmm.c"

$(IntermediateDirectory)/KMmHelper.c$(ObjectSuffix): KMmHelper.c $(IntermediateDirectory)/KMmHelper.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/irvan/DATA/Jaura/KMmHelper.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/KMmHelper.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/KMmHelper.c$(DependSuffix): KMmHelper.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/KMmHelper.c$(ObjectSuffix) -MF$(IntermediateDirectory)/KMmHelper.c$(DependSuffix) -MM "KMmHelper.c"

$(IntermediateDirectory)/KMmHelper.c$(PreprocessSuffix): KMmHelper.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/KMmHelper.c$(PreprocessSuffix) "KMmHelper.c"

$(IntermediateDirectory)/KFrame.c$(ObjectSuffix): KFrame.c $(IntermediateDirectory)/KFrame.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/irvan/DATA/Jaura/KFrame.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/KFrame.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/KFrame.c$(DependSuffix): KFrame.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/KFrame.c$(ObjectSuffix) -MF$(IntermediateDirectory)/KFrame.c$(DependSuffix) -MM "KFrame.c"

$(IntermediateDirectory)/KFrame.c$(PreprocessSuffix): KFrame.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/KFrame.c$(PreprocessSuffix) "KFrame.c"

$(IntermediateDirectory)/DList.c$(ObjectSuffix): DList.c $(IntermediateDirectory)/DList.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/irvan/DATA/Jaura/DList.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/DList.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/DList.c$(DependSuffix): DList.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/DList.c$(ObjectSuffix) -MF$(IntermediateDirectory)/DList.c$(DependSuffix) -MM "DList.c"

$(IntermediateDirectory)/DList.c$(PreprocessSuffix): DList.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/DList.c$(PreprocessSuffix) "DList.c"

$(IntermediateDirectory)/SList.c$(ObjectSuffix): SList.c $(IntermediateDirectory)/SList.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/irvan/DATA/Jaura/SList.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SList.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SList.c$(DependSuffix): SList.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SList.c$(ObjectSuffix) -MF$(IntermediateDirectory)/SList.c$(DependSuffix) -MM "SList.c"

$(IntermediateDirectory)/SList.c$(PreprocessSuffix): SList.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SList.c$(PreprocessSuffix) "SList.c"

$(IntermediateDirectory)/KMalloc.c$(ObjectSuffix): KMalloc.c $(IntermediateDirectory)/KMalloc.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/irvan/DATA/Jaura/KMalloc.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/KMalloc.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/KMalloc.c$(DependSuffix): KMalloc.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/KMalloc.c$(ObjectSuffix) -MF$(IntermediateDirectory)/KMalloc.c$(DependSuffix) -MM "KMalloc.c"

$(IntermediateDirectory)/KMalloc.c$(PreprocessSuffix): KMalloc.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/KMalloc.c$(PreprocessSuffix) "KMalloc.c"

$(IntermediateDirectory)/Device.c$(ObjectSuffix): Device.c $(IntermediateDirectory)/Device.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/irvan/DATA/Jaura/Device.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Device.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Device.c$(DependSuffix): Device.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Device.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Device.c$(DependSuffix) -MM "Device.c"

$(IntermediateDirectory)/Device.c$(PreprocessSuffix): Device.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Device.c$(PreprocessSuffix) "Device.c"

$(IntermediateDirectory)/ATA.c$(ObjectSuffix): ATA.c $(IntermediateDirectory)/ATA.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/irvan/DATA/Jaura/ATA.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ATA.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ATA.c$(DependSuffix): ATA.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ATA.c$(ObjectSuffix) -MF$(IntermediateDirectory)/ATA.c$(DependSuffix) -MM "ATA.c"

$(IntermediateDirectory)/ATA.c$(PreprocessSuffix): ATA.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ATA.c$(PreprocessSuffix) "ATA.c"

$(IntermediateDirectory)/PIT.c$(ObjectSuffix): PIT.c $(IntermediateDirectory)/PIT.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/irvan/DATA/Jaura/PIT.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PIT.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PIT.c$(DependSuffix): PIT.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PIT.c$(ObjectSuffix) -MF$(IntermediateDirectory)/PIT.c$(DependSuffix) -MM "PIT.c"

$(IntermediateDirectory)/PIT.c$(PreprocessSuffix): PIT.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PIT.c$(PreprocessSuffix) "PIT.c"

$(IntermediateDirectory)/PIC.c$(ObjectSuffix): PIC.c $(IntermediateDirectory)/PIC.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/irvan/DATA/Jaura/PIC.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PIC.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PIC.c$(DependSuffix): PIC.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PIC.c$(ObjectSuffix) -MF$(IntermediateDirectory)/PIC.c$(DependSuffix) -MM "PIC.c"

$(IntermediateDirectory)/PIC.c$(PreprocessSuffix): PIC.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PIC.c$(PreprocessSuffix) "PIC.c"

$(IntermediateDirectory)/Tmpfs.c$(ObjectSuffix): Tmpfs.c $(IntermediateDirectory)/Tmpfs.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/irvan/DATA/Jaura/Tmpfs.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Tmpfs.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Tmpfs.c$(DependSuffix): Tmpfs.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Tmpfs.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Tmpfs.c$(DependSuffix) -MM "Tmpfs.c"

$(IntermediateDirectory)/Tmpfs.c$(PreprocessSuffix): Tmpfs.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Tmpfs.c$(PreprocessSuffix) "Tmpfs.c"

$(IntermediateDirectory)/KFilesystem.c$(ObjectSuffix): KFilesystem.c $(IntermediateDirectory)/KFilesystem.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/irvan/DATA/Jaura/KFilesystem.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/KFilesystem.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/KFilesystem.c$(DependSuffix): KFilesystem.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/KFilesystem.c$(ObjectSuffix) -MF$(IntermediateDirectory)/KFilesystem.c$(DependSuffix) -MM "KFilesystem.c"

$(IntermediateDirectory)/KFilesystem.c$(PreprocessSuffix): KFilesystem.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/KFilesystem.c$(PreprocessSuffix) "KFilesystem.c"

$(IntermediateDirectory)/Fnode.c$(ObjectSuffix): Fnode.c $(IntermediateDirectory)/Fnode.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/irvan/DATA/Jaura/Fnode.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Fnode.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Fnode.c$(DependSuffix): Fnode.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Fnode.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Fnode.c$(DependSuffix) -MM "Fnode.c"

$(IntermediateDirectory)/Fnode.c$(PreprocessSuffix): Fnode.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Fnode.c$(PreprocessSuffix) "Fnode.c"

$(IntermediateDirectory)/File.c$(ObjectSuffix): File.c $(IntermediateDirectory)/File.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/irvan/DATA/Jaura/File.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/File.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/File.c$(DependSuffix): File.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/File.c$(ObjectSuffix) -MF$(IntermediateDirectory)/File.c$(DependSuffix) -MM "File.c"

$(IntermediateDirectory)/File.c$(PreprocessSuffix): File.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/File.c$(PreprocessSuffix) "File.c"

$(IntermediateDirectory)/FAT16.c$(ObjectSuffix): FAT16.c $(IntermediateDirectory)/FAT16.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/irvan/DATA/Jaura/FAT16.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FAT16.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FAT16.c$(DependSuffix): FAT16.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/FAT16.c$(ObjectSuffix) -MF$(IntermediateDirectory)/FAT16.c$(DependSuffix) -MM "FAT16.c"

$(IntermediateDirectory)/FAT16.c$(PreprocessSuffix): FAT16.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/FAT16.c$(PreprocessSuffix) "FAT16.c"

$(IntermediateDirectory)/Interrupt.c$(ObjectSuffix): Interrupt.c $(IntermediateDirectory)/Interrupt.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/irvan/DATA/Jaura/Interrupt.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Interrupt.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Interrupt.c$(DependSuffix): Interrupt.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Interrupt.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Interrupt.c$(DependSuffix) -MM "Interrupt.c"

$(IntermediateDirectory)/Interrupt.c$(PreprocessSuffix): Interrupt.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Interrupt.c$(PreprocessSuffix) "Interrupt.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


