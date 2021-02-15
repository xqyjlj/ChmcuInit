using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace ChmcuInit.Models
{
    public class ViewChipConfigChooseChipSelectableModel : INotifyPropertyChanged
    {
        private bool _选中;
        private string _名字;

        public bool 是否选中
        {
            get => _选中;
            set
            {
                if (_选中 == value) return;
                _选中 = value;
                OnPropertyChanged();
            }
        }

        public string 名字
        {
            get => _名字;
            set
            {
                if (_名字 == value) return;
                _名字 = value;
                OnPropertyChanged();
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
            => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}
