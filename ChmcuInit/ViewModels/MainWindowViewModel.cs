using ChmcuInit.Views;
using Prism.Commands;
using Prism.Mvvm;
using Prism.Regions;
using System;

namespace ChmcuInit.ViewModels
{
    public class MainWindowViewModel : BindableBase
    {
        private string _title = "ChMcuInit";

        public DelegateCommand OpenStartViewCommand { get;private set; }
        public DelegateCommand OpenChipConfigViewCommand { get;private set; }

        public string Title
        {
            get { return _title; }
            set { SetProperty(ref _title, value); }
        }

        private readonly IRegionManager regionManger;

        public MainWindowViewModel(IRegionManager regionManger)
        {
            this.regionManger = regionManger;

            OpenStartViewCommand = new DelegateCommand(OpenStartView);
            OpenChipConfigViewCommand =new DelegateCommand(OpenChipConfigView);

            regionManger.RegisterViewWithRegion("MainWindowContentRegion", typeof(ViewStart));
        }

        private void OpenStartView()
        {
            regionManger.RequestNavigate("MainWindowContentRegion", "ViewStart");
        }

        private void OpenChipConfigView()
        { 
            regionManger.RequestNavigate("MainWindowContentRegion", "ViewChipConfig");
        }
    }
}
