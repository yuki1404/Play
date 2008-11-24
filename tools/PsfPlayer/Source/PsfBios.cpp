#include "PsfBios.h"
#include "PsfVm.h"

using namespace PS2;
using namespace std;

#define PSF_DEVICENAME	"psf"

CPsfBios::CPsfBios(CMIPS& cpu, uint8* ram, uint32 ramSize) :
m_bios(0x1000, CPsfVm::CLOCK_FREQ, cpu, ram, ramSize, NULL),
m_psfDevice(new CPsfDevice())
{
	m_bios.Reset();

    Iop::CIoman* ioman = m_bios.GetIoman();
    ioman->RegisterDevice(PSF_DEVICENAME,	m_psfDevice);
	ioman->RegisterDevice("host0",			m_psfDevice);
}

CPsfBios::~CPsfBios()
{

}

void CPsfBios::AppendArchive(const CPsfBase& psfFile)
{
	static_cast<CPsfDevice*>(m_psfDevice.get())->AppendArchive(psfFile);
}

void CPsfBios::Start()
{
    string execPath = string(PSF_DEVICENAME) + ":/psf2.irx";
    m_bios.LoadAndStartModule(execPath.c_str(), NULL, 0);
}

void CPsfBios::HandleException()
{
	m_bios.HandleException();
}

void CPsfBios::HandleInterrupt()
{
	m_bios.HandleInterrupt();
}

void CPsfBios::CountTicks(uint32 ticks)
{
	m_bios.CountTicks(ticks);
}

#ifdef DEBUGGER_INCLUDED

void CPsfBios::LoadDebugTags(const char* packagePath)
{

}

void CPsfBios::SaveDebugTags(const char* packagePath)
{

}

#endif
