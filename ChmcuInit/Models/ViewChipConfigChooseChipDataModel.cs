using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace ChmcuInit.Models
{
    public class ViewChipConfigChooseChipDataModel : INotifyPropertyChanged
    {
        private string _型号;

        public string 型号
        {
            get => _型号;
            set
            {
                if (_型号 == value) return;
                _型号 = value;
                OnPropertyChanged();
            }
        }

        private string _状态;

        public string 状态
        {
            get => _状态;
            set
            {
                if (_状态 == value) return;
                _状态 = value;
                OnPropertyChanged();
            }
        }

        private string _价格每千片;

        public string 价格每千片
        {
            get => _价格每千片;
            set
            {
                if (_价格每千片 == value) return;
                _价格每千片 = value;
                OnPropertyChanged();
            }
        }

        private string _封装;

        public string 封装
        {
            get => _封装;
            set
            {
                if (_封装 == value) return;
                _封装 = value;
                OnPropertyChanged();
            }
        }

        private string _Flash;

        public string Flash
        {
            get => _Flash;
            set
            {
                if (_Flash == value) return;
                _Flash = value;
                OnPropertyChanged();
            }
        }

        private string _Ram;

        public string Ram
        {
            get => _Ram;
            set
            {
                if (_Ram == value) return;
                _Ram = value;
                OnPropertyChanged();
            }
        }

        private string _IO;

        public string IO
        {
            get => _IO;
            set
            {
                if (_IO == value) return;
                _IO = value;
                OnPropertyChanged();
            }
        }

        private string _频率;

        public string 频率
        {
            get => _频率;
            set
            {
                if (_频率 == value) return;
                _频率 = value;
                OnPropertyChanged();
            }
        }
        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
            => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}
