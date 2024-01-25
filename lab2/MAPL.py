import math
import matplotlib.pyplot as plt 
import numpy as np

def print_graph(PLd,ddl,dul):
    plt.figure(1)
    plt.xlabel("Distance")
    plt.ylabel("Loss")
    plt.plot(PLd)
    plt.axhline(MAPL_UL, color="red", label = 'mapl ul',linestyle ='dashed')
    plt.axhline(MAPL_DL, color="yellow",label = 'mapl dl',linestyle ='dashed')
    plt.axvline(ddl, color="yellow",label ='distance dl')
    plt.axvline(dul, color="red",label ='distance dl')
    plt.legend()
    plt.show()

def UMiNLOS(PLd):
    dul = 0
    ddl = 0
    i = 0
    for i in range(1,3000):
        per = 26 * math.log10(1.8) + 22.7 + 36.7 * math.log10(i)
        PLd.append( 26 * math.log10(1.8) + 22.7 + 36.7 * math.log10(i))

        if round(per,1) == round(MAPL_DL,1):
            ddl = i
        if round(per,1) == round(MAPL_UL,1):
            dul = i

    print(ddl)
    print(dul)
    print('Uminlos  (S=100кв.км) R =',dul,'[м]', '   Кол-во BS =', int(5000**2/(3*1.95*dul**2)))
    print_graph(PLd,ddl,dul)

def COST231(PLd):
    dul =0
    ddl = 0
    i = 0
    A=B=0
    hBS = 50
    hms = 3
    a=s=0
    Lclutter = 0
    h_BW = 1.8
    f = 1.8e9 # [ГГц] Диапозон частот

    if (f > 150e6) and (f < 1500e6):
        A = 69.55
        B = 26.16
    elif (f > 1500e6) and (f < 2000e6):
        A = 46.3
        B = 33.9
    print("Enter a:\n1.Плотная застройка\n2.Город\n3.Пригород\n4.Сельская местность\n5.Трасса\n")

    butb = int
    butb = int(input(butb))
    
    match butb:
        case 1:
            Lclutter = 3#DU
            a = 3.2 * (math.log10(11.75 * hms)**2)- 4.97 #DU & U
        case 2:

            Lclutter = 0#U
            a = 3.2 * (math.log10(11.75 * hms)**2)- 4.97 #DU & U
        case 3:
            Lclutter = -((2*(math.log10((f/1e6)/28)**2))+5.4)#SU
            a = (1.1 * math.log10(f/1e6) * hms - (1.56 * math.log10(f/1e6) - 0.8)) #SU & RURAL & 
        case 4:
            Lclutter = -(4.78*(math.log10(f/1e6)**2)-18.33*(math.log10(f/1e6))+40.94)#RURAL
            a = (1.1 * math.log10(f/1e6) * hms - (1.56 * math.log10(f/1e6) - 0.8)) #SU & RURAL & ROAD
        case 5:
            Lclutter = -(4.78*(math.log10(f/1e6)**2)-18.33*(math.log10(f/1e6))+35.94)#ROAD
            a = (1.1 * math.log10(f/1e6) * hms - (1.56 * math.log10(f/1e6) - 0.8)) #SU & RURAL & ROAD
        case _:
            print("not")

    print("a=",a,"\n")
    print("s=",s,"\n")
    print("Lc=",Lclutter,"\n")
    for i in range(1,30000):
        if i < 1000:
            s = (47.88 + 13.9 * math.log10(f/1e6) - 13.9 * math.log10(hBS)) * (1/math.log10(50))
        elif i >= 1000:
            s = 44.9 - 6.55 * math.log10(f/1e6)

        per = A + B * math.log10(f/1e6) - 13.82 * math.log10(hBS) - a + s * math.log10(i/1000) + Lclutter
        PLd.append(A + B * math.log10(f/1e6) - 13.82 * math.log10(hBS) - a + s * math.log10(i/1000) + Lclutter)

        round_k = 1
        if round(per,round_k) == round(MAPL_DL,round_k):
            ddl = i
        if round(per,round_k) == round(MAPL_UL,round_k):
            dul = i
    print(ddl)
    print(dul)
    print('cost  (S=100кв.км) R =',dul,'[м]', '   Кол-во BS =', int(100000**2/(3*1.95*dul**2)))

    print_graph(PL,ddl,dul)

def Walfish_Ikegami_LOS(PLd):
    f = 1.8e9 # [ГГц] Диапозон частот
    dul =0
    ddl = 0
    for i in range(30,10000):
        per = 42.6 + 20*math.log10(f/1e9) + 26*math.log10(i)
        PLd.append(42.6 + 20*math.log10(f/1e9) + 26*math.log10(i))

        round_k = 2
        if round(per,round_k) == round(MAPL_DL,round_k):
            ddl = i
        if round(per,round_k) == round(MAPL_UL,round_k):
            dul = i
    print("distance dl",ddl)
    print("distance ul",dul)
    print('Walfish_Ikegami_LOS  (S=100кв.км) R =',dul,'[м]', '   Кол-во BS =', int(100000**2/(3*1.95*dul**2)))
    print_graph(PLd,ddl,dul)
    
def Walfish_Ikegami_Non_LOS(PLd):
    hBS = 50 #[м]   #(при высоте подвеса антенны базовой станции от 4 до 50 м)
    w = 200 #средняя ширина улиц, м
    h = 49 #средняя высота зданий, м
    hms = 1.5  #[м]   #(при высоте антенны мобильного устройства от 1 до 10 м)
    b = 200 # среднее расстояние между зданиями, м

    f = 1.8e6 # [ГГц] Диапозон частот

    L1 = -16.9 - 10*math.log10(w) + 10*math.log10(f/1e9) + 20*math.log10(h - hms) + (-10 + 0.354*0)
    ka = 54
    kb = 18
    kf = -4 + 0.7* ((f/1e9)/925 - 1)

    dul =0
    ddl = 0
    for i in range(30,6000):
        L0 = 32.44 + 20*math.log10(f/1e9) + 20*math.log10(i)
        L2 = (18*math.log10(1+hBS)) + ka + kb*math.log10(i) + kf*math.log10(b)
        if (L1+L2 > 0):
            PLd.append(L0 + L1 + L2)
            per = L0 + L1 + L2
        else:
            PLd.append( L0 )
            per = L0

        round_k = 0
        if round(per,round_k) == round(MAPL_DL,round_k):
            ddl = i
        if round(per,round_k) == round(MAPL_UL,round_k):
            dul = i
        if ddl and dul == 0:
            print_graph(PLd,MAPL_DL,MAPL_UL)
    print("distance dl",ddl)
    print("distance ul",dul)
    print('Walfish_Ikegami_NLOS  (S=100кв.км) R =',dul,'[м]', '   Кол-во BS =', int(100000**2/(3*1.95*dul**2)))
    print_graph(PLd,ddl,dul)
    

#Входные данные:
TX_Powers_BS = 46 #[dBm] Мощность передатчика базовой станции
TX_Powers_UE = 24 #[dBm] Мощность передатчика абоненстской станции
Ant_Gains_BS = 21 #[dBi] коэффицент усиления приемо-передающей антенны базовой станции
Penetration_M = 15 #[dB] запас сигнала на проникновение сквозь стены
Interpheration_M = 1 #[dB] запас мощности на интерференцию
r = 1 #[m]
S_BS = 1.95*r**2 #[m**2]
S_ter = 100*10**5 #[m**2]
PL_d = 1 #[dB]
Feeder_LOSS = 2 # [dB]
MIMO_Gain = 3*2 # [dB]
# 1) Выполните расчет бюджета восходящего канала, используя входные данные и определите уровень максимально допустимых потерь сигнала MAPL_UL.
# Формула для расчёта: TX_Power_UE - Feeder_LOSS + Ant_Gain_BS + MIMO_Gain - PL(d) (MAPL_UL) - IM - Penetration_M >= RX_Sens_BS

# 1.1) Найдём RX_Sens_BS ( Noise_Figure + Thermal_Noise + Reqired_SINR ):
BW = 1.8*10**7 # Полоса частот в DL и UL
Thermal_Noise = -174 + 10*math.log10(BW)
Noise_Figure_BS = 2.4 # [dB] Коэффициент шума приемника BS
Reqired_SINR_BS = 4 # [dB] Требуемое отношение SINR для UL

RX_Sens_BS = Noise_Figure_BS + Thermal_Noise + Reqired_SINR_BS
#print("RX_Sens_BS: ",RX_Sens_BS)

# 1.2) Найдём MAPL_UL :
MAPL_UL = (RX_Sens_BS - TX_Powers_UE + Feeder_LOSS - Ant_Gains_BS - MIMO_Gain + Interpheration_M + Penetration_M) * -1
print("\nMAPL_UL: ",MAPL_UL)
#RX_Sens_BS2 = TX_Powers_UE - Feeder_LOSS + Ant_Gains_BS + MIMO_Gain - MAPL_UL - Interpheration_M - Penetration_M 
#print(RX_Sens_BS2)

# 2) Выполните расчет бюджета нисходящего канала, используя входные данные и определите уровень максимально допустимых потерь сигнала MAPL_DL.

# Формула для расчёта: TX_Power_BS - Feeder_LOSS + Ant_Gain_BS + MIMO_Gain - PL(d) (MAPL_DL) - IM - Penetration_M >= RX_Sens_US

# Найдём RX_Sens_UE ( Noise_Figure + Thermal_Noise + Reqired_SINR ):
Noise_Figure_UE = 6 # [dB] Коэффициент шума приемника DL
Reqired_SINR_UE = 2 # [dB] Требуемое отношение SINR для DL

RX_Sens_UE = Noise_Figure_UE + Thermal_Noise + Reqired_SINR_UE
#print("RX_Sens_UE: ",RX_Sens_UE)

# 2.2) Найдём MAPL_DL :
MAPL_DL = (RX_Sens_UE - TX_Powers_BS + Feeder_LOSS - Ant_Gains_BS - MIMO_Gain + Interpheration_M + Penetration_M) * -1
print ("MAPL_DL: ",MAPL_DL,"\n")

PL = []
#UMiNLOS(PL)
#COST231(PL)
#Walfish_Ikegami_LOS(PL)

print("Enter a:\n1.UMiNLOS()\n2.COST231()\n3.Walfish_Ikegami_LOS()\n4.Walfish_Ikegami_NLOS()\n5")
buta = int
buta = 4
buta = int(input(buta))


match buta:
    case 1: 
        UMiNLOS(PL)
    case 2:
        COST231(PL)
    case 3:
        Walfish_Ikegami_LOS(PL)
    case 4:
        Walfish_Ikegami_Non_LOS(PL)
    case _:
        print("not")


