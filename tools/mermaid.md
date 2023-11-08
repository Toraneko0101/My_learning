## フローチャート
```mermaid
graph TD;
    A-->B;
    A-->C;
    B-->D;
    C-->D;
```

## シーケンス図
```
participantに追加した順番に左から表示されるっぽい
Note right ofで説明を追加
```
```mermaid
sequenceDiagram
    participant 太郎
    participant 花子
    太郎->>花子: ねえ、今ちょっと時間ある？
    loop Healthcheck
        花子->>花子: 別に用はないけど、相手するのめんどいなあ
    end
    Note right of 花子: 用事あるって嘘ついちゃお
    花子->>太郎: ごめん、今日は忙しくって
    花子->>次郎: この後、食事でもどう？
    次郎->>花子: いいね、じゃあ7時くらいにいつもの店で
```

## ガントチャート
```
excludesで休日や祝日を考慮する
weekendsで休日を省く
```
```mermaid
gantt
dateFormat YYYY-MM-DD
title 2023年11月予定
excludes weekends 2023-11-03 2023-11-23

section A section
完了したタスク      :done, des1, 2023-11-01,2023-11-03
アクティブなタスク  :active, des2, 2023-11-03, 3d
未来のタスク        :       des3, after des2, 5d
別の未来のタスク    :       des4, after des3, 5d
```

## クラス図
```mermaid
classDiagram
    Animal --|> Bird
    Animal --|> Fish
    Animal --|> Penguin
    Animal : +int age
    Animal : +String gender
    Animal : +born()
    Animal : +is_like(food) bool
    class Bird{
        +String beakColor
        +fly()
    }
    class Fish{
        -int sizeInFeet
        +swim()
        -Eat()
    }
    class Penguin{
        +int dive_meters
        +run()
        +swim()
    }

```

Gitグラフ
```mermaid

gitGraph
    commit
    commit
    branch development
    commit
    commit
    branch issue1
    commit
    checkout development
    merge issue1
    branch issue2
    commit
    checkout development
    merge issue2
    checkout main
    merge development
```

## ユーザージャーニー図
```mermaid
journey
    title My working day
    section Go to work
        Eat breakfast: 3: Me
        Go to office: 1: Me
        Do work: 2: Me, boss
        Going home: 1: Me
    section Go home
        learn program: 3: Me
        create game: 5: Me
        write novel: 4: Me
        Sleep: 5: Me
```

## ステータス図
```mermaid
stateDiagram-v2
    state if_state<<choice>>
    [*] --> IsPositive
    IsPositive --> if_state
    if_state --> False: if i < 100
    if_state --> True: if i >= 100
```

## 円グラフ
```mermaid
pie showData
    title 23年度売上割合
    "Tシャツ" : 67.12
    "缶バッジ" : 21.2
    "タオル" : 11.34
    "その他" : 0.34

```

## ER図
```
0| 最小値0,　最大値1
0{ 最小値0, 最大値上限なし
```
```mermaid
---
title: 顧客情報
---
erDiagram
    "顧客情報" {
        string ID PK
        string name
        string Fname
        string Order FK
        long count
        date time
        bool finish
    }
    "商品情報"{
        string Order PK
        long sizeX
        long sizeY
        long sizeZ
        long weight
    }

    "顧客情報" ||--|{ "商品情報" : Order
```

## Mindmap
```mermaid
mindmap
    root((猫))
        動物
        かわいい
        爪とぎ
            ストレス
            マーキング
            気分転換
                休憩
        野良
            寿命
            黒猫
            雑種
        ウォーリアーズ
            ファイアスター
            エリン・ハンター

```