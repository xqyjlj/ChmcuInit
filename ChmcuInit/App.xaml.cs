using ChmcuInit.Views;
using Prism.Ioc;
using System.Windows;

namespace ChmcuInit
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App
    {
        protected override Window CreateShell()
        {
            return Container.Resolve<MainWindow>();
        }

        protected override void RegisterTypes(IContainerRegistry containerRegistry)
        {
            containerRegistry.RegisterForNavigation<ViewStart>();
            containerRegistry.RegisterForNavigation<ViewChipConfig>();
            containerRegistry.RegisterForNavigation<ViewChipConfigChoose>();
        }
    }
}
