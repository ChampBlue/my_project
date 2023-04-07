import sys
import threading
import random

class Master:
    def __init__(self, name):
        self.name = name
        self.money = 100
        self.food = 10
        self.water = 10
        self.tired = 0
        
        self.food = max(self.food, 0)
        self.tired = max(self.tired, 0)
        self.water = max(self.water, 0)
        self.money = max(self.money, 0)
    
class Rak:
    def __init__(self):
        self.name = '손영락'
        self.age = 0
        self.height = 50
        self.weight = 20
        self.mentality = 100
        self.hunger = 100
        self.thirst = 100
        self.clean = 100
        self.penis_size = 1
        
        self.mentality = max(self.mentality, 0)
        self.hunger = max(self.hunger, 0)
        self.hunger = min(self.hunger, 100)
        self.thirst = max(self.thirst, 0)
        self.thirst = min(self.thirst, 100)
        self.clean = max(self.clean, 0)
        self.clean = min(self.clean, 100)


player_name = input("플레이어 이름을 설정하시오 : ")
master = Master(player_name)
rak = Rak()

def time_increment():
    rak.age += 0.1
    if rak.hunger > 30 and rak.thirst > 30:
        rak.height += 1 
        rak.weight += 1
    rak.mentality -= 5
    rak.hunger -= 5
    rak.thirst -= 5
    rak.clean -= 5

    threading.Timer(60.0, time_increment).start()

def feed_rak (player_food):
    try:
        if player_food > master.food:
            raise ValueError("먹이의 양이 모자랍니다!")

        master.food -= player_food
        rak.hunger += player_food 
        rak.clean -= 5
    
    except ValueError as e:
        print(e)

def drunk_rak(player_water):
    try:
        if player_water > master.water:
            raise ValueError("물의 양이 모자랍니다!")

        master.water -= player_water
        rak.thirst += player_water 
        rak.clean -= 2
    
    except ValueError as e:
        print(e)

def play_rak(choice):
    if choice == 1:
        master.tired += 20
        rak.mentality += 10

    elif choice == 2:
        master.money -= 10
        rak.mentality += 10

    elif choice == 3:
        master.money -= 30    
        rak.mentality += 30
        if random.random() < 0.01:
            print("마사지를 받으면서 이렇게 잘 참는 놈은 처음이군...")
            print("하지만 이건 참을 수 없을껄!!!")
            print("와랄랄랄라")
            print("영락이는 참을 수 없었다...")
            rak.penis_size += 5
            rak.mentality -= 50
            
def clean_rak():
    master.water -= 10
    rak.clean += 10
    if random.random() < 0.01:
        print("영락이 : 아앗... 거긴...")
        print(f"{master.name} : 크흠... 등짝... 등짝을 보자꾸나!!!")
        print("......")
        rak.penis_size += 5
        rak.mentality += 20
        master.tired -= 50

def sell_rak():
    print('1. 신안 염전')
    print('2. 배우 매니지먼트 회사')
    choice = int(input('영락이를 어디에 파시겠습니까? : '))
    try:
        if choice < 0 and choice > 2:
            raise ValueError("1 또는 2 중에서 골라주시오")
        if(choice == 1):
            try:
                if rak.height < 190 and rak.weight < 100:
                    raise ValueError("아직 더 성장 해야 합니다!")
                master.money += 10000
                del rak
                print("영락이는 신안 염전으로 떠납니다...")
                print(f"{master.name}님은 영락이를 잘 키워서 1억원에 팔았습니다.")
                print("다음 영락이도 잘 키워 주십시오")
                print("게임을 종료합니다...")
                sys.exit(0)            
            except ValueError as e:
                print(e)

        if(choice == 2):
            try:
                if rak.penis_size < 30:
                    raise ValueError('아직 더 성장 해야 합니다.')
                master.money += 100000
                del rak
                print("영락이는 배우가 되기 위해 배우 매니지먼트 회사로 떠납니다...")
                print(f"{master.name}님은 영락이를 잘 키워서 10억원에 팔았습니다.")
                print("다음 영락이도 잘 키워 주십시오")
                print("게임을 종료합니다...")
                sys.exit(0)          
            except ValueError as e:
                print(e)
    except ValueError as er:
        print(er)

def call_master_menu():
    print('1. 도박')
    print('2. 휴식')
    print('3. 일하기')
    print('4. 물품 사기')
    choice = int(input('플레이어 메뉴를 선택 하시오 : '))
    try:
        if choice < 0 and choice > 4:
            raise ValueError('1 ~ 4 중에서 선택하시오!')

        if choice == 1:
            try:
                bet_coin = int(input('베팅할 돈은? : '))
                print(f"현재 {master.name}님의 돈은 {master.money}만원 만큼 있습니다.")
                if bet_coin > master.money:
                    raise ValueError('돈이 모자랍니다!!!')
                master.money -= bet_coin

                if random.random() < 0.1:
                    master.money += bet_coin * 2
                elif random.random() < 0.05:
                    master.money += bet_coin * 5    
                elif random.random() < 0.01:
                    master.money += bet_coin * 10
                else:
                    master.money = master.money
            except ValueError as er:
                print(er)

        if choice == 2:
            try:
                if master.money < 20:
                    raise ValueError("돈이 모자랍니다.")
                
                master.money -= 20
                master.tired += 30

            except ValueError as er:
                print(er)

        if choice == 3:
            try:
                if master.tired < 30:
                    raise ValueError("휴식이 필요합니다.")
                
                master.money += 20
                master.tired -= 30

            except ValueError as er:
                print(er)
                
        if choice == 4:
            try:
                sell_food = int(input("사료를 얼마나 사실 껀가요? : "))
                if sell_food * 1 > master.money:
                    raise ValueError('돈이 모자랍니다!')
                
                master.money -= sell_food * 1
                master.food += sell_food *1

                sell_water = int(input("물을 얼마나 사실 껀가요? : "))
                if sell_water * 1 > master.money:
                    raise ValueError('돈이 모자랍니다!')
                
                master.money -= sell_water * 1
                master.water += sell_water *1
            
            except ValueError as er:
                print(er)

    except ValueError as e:
        print(e)    

def show_master_status():
    print('**' * (len(master.name) + 6))
    print(f"{master.name}님의 상태창")
    print('**' * (len(master.name) + 6))
    print(f"현재 돈 : {master.money}")
    print(f"현재 남은 먹이 : {master.food}")
    print(f"현재 남은 물 : {master.water}")
    print(f"현재 피로도 : {master.tired}")
    print('\n')

def show_rak_status():
    print('**' * (len(rak.name) + 5))
    print('영락이의 상태창')
    print('**' * (len(rak.name) + 5))
    print(f'영락이 나이 : {rak.age}')
    print(f'영락이 키 : {rak.height}')
    print(f'영락이 몸무게 : {rak.weight}')
    print(f'영락이 공복상태 : {rak.hunger}')
    print(f'영락이 정신상태 : {rak.mentality}')
    print(f'영락이 청결상태 : {rak.clean}')
    print(f'영락이 쥬지 상태 : {rak.penis_size}')
    print('\n')

def warning():
    if rak.hunger < 10:
        print('위험!!! 영락이가 아사 직전입니다!!!')
    if rak.thirst < 10:
        print('위험!!! 영락이가 탈수 직전입니다!!!')
    if rak.mentality < 10:
        print('위험!!! 영락이의 멘탈이 깨지기 직전입니다!!!')
    if rak.clean < 10:
        print('위험!!! 영락이가 더러워서 병에 걸리기 직전입니다!!!')
    

def main():
    time_increment()

    while(True):
        warning()
        try:
            print('=' * 20)
            print('메뉴')
            print('1. 밥과 물 주기')
            print('2. 놀아주기')
            print('3. 씻기기')
            print('4. 플레이어 메뉴')
            print('5. 영락이 팔아버리기')
            print('6. 상태창')
            print('7. 게임 종료')
            print('=' * 20)

            menu = int(input('메뉴를 선택해 주세요 : '))
            if menu < 0 and menu > 6:
                raise ValueError("메뉴 번호를 다시 한번 확인하세요")
            
        except ValueError as e:
            print(e)

        if menu == 1:
            player_food = int(input('먹일 먹이량을 적어 주세요 : '))
            player_water = int(input('마시게 할 물량을 적어 주세요 : '))
            feed_rak(player_food)
            drunk_rak(player_water)

        elif menu == 2:
            try:
                print('1. 원반 던지기')
                print('2. 애니멀 카페 데려가기')
                print('3. 마사지 시켜주기')
                choice = int(input("영락이와 뭘 하고 놀아 줄까요?"))
                if choice < 0 and choice > 3:
                    raise ValueError("1 ~ 3 사이 값을 입력하시오!")
                play_rak(choice)

            except ValueError as e:
                print(e)

        elif menu == 3:
            clean_rak()

        elif menu == 4:
            call_master_menu()

        elif menu == 5:
            sell_rak()

        elif menu == 6:
            show_master_status()
            show_rak_status()
        
        elif menu == 7:
            print('게임을 종료합니다.')
            sys.exit(0)
            
if __name__ == "__main__":
    main()
