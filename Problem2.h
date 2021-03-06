//---------------------------------------------------------------------------

#ifndef Problem2H
#define Problem2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Edit.hpp>
//---------------------------------------------------------------------------
class TItem2 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TCircle *pWait;
	TCircle *pInside;
	TCircle *pDone;
	TButton *tStart;
	TButton *tChange;
	TEdit *InsideEdit;
	TEdit *DoneEdit;
	TLabel *Label4;
	TLabel *labelinside;
	TLabel *label;
	TEdit *WaitEdit;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *labeldone;
	TButton *Button3;
	TLabel *pWait2;
	TLabel *pInside2;
	TLabel *pDone2;
	TLine *Line1;
	TLine *Line2;
	TLine *Line3;
	TLine *Line4;
	TLabel *Label9;
	TLabel *Label10;
	TLine *Line16;
	TLine *Line15;
	TLine *Line5;
	TLine *Line6;
	TLine *Line7;
	TLine *Line8;
	TLine *Line9;
	TLine *Line10;
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall tStartClick(TObject *Sender);
	void __fastcall tChangeClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TItem2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TItem2 *Item2;
//---------------------------------------------------------------------------
#endif
