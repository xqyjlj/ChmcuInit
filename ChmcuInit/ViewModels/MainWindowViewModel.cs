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

            regionManger.RegisterViewWithRegion("ContentRegion", typeof(StartView));
        }

        private void OpenStartView()
        {
            regionManger.RequestNavigate("ContentRegion", "StartView");
        }

    }
}
