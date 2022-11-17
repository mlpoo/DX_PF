#include "stdafx.h"
#include "MapEditor.h"
#include "Manager/Singleton.h"

void MapEditor::Start()
{
    Str = "Collider";
    Create();
    CollisionImage = { "CollisionImage", { 1280 * 4.5f ,  1040 * 4.5f },   0, { 0, 0 } };
    SetType(OperationType::OT_Location);
    Value = 0.01f;
}

bool MapEditor::Update()
{
    Camera.Set();

    if (Input::Get::Key::Down(VK_F12))
        GetSceneManager->ChangeScene("Scene1");

    if (Input::Get::Key::Down(VK_F1)) Create();
    
    if (Input::Get::Key::Down(VK_F2)) Print();

    if (Input::Get::Key::Down(VK_F3)) Input();


    if (Input::Get::Key::Down(0x31)) SetType(OperationType::OT_Location);
    if (Input::Get::Key::Down(0x32)) SetType(OperationType::OT_Rotation);
    if (Input::Get::Key::Down(0x33)) SetType(OperationType::OT_Scale);
    
    Operation();

    CollisionImage.Draw();

    for (auto & elem : Collisions)
        elem.Draw();

    return true;
}

void MapEditor::End()
{
}

void MapEditor::Print() const
{
    int input = 0;


    printf("[ 1. Image 로 출력 ]  [ 2. Collision 으로 출력 ] \n");
    printf("Input : ");
    scanf_s("%d", &input);

    if (input == 1)
    {
        printf("HeaderFile \n");
        printf("Rendering::Image::Component Images[%lld]; \n", Collisions.size());

        printf("\nCppFile\n");

        int i =  0;

        for (Rendering::Image::Component const& elem : Collisions)
        {

            printf("Collision[%i] = { \"%s\" , { %.1f, %.1f } , { 0.0f , 0.0f , %.1f } , { %.1f, %.1f }, 1.0f }; \n",
                i, elem.Content ,elem.Length[0], elem.Length[1], elem.Angle[2], elem.Location[0], elem.Location[1]);
            ++i;
        }
    }
    else if (input == 2)
    {
        printf("HeaderFile \n");
        printf("Collision::RectAngle Collisions[%lld]; \n", Collisions.size());

        int i = 0;

        printf("\nCppFile\n");

        for (Rendering::Image::Component const& elem : Collisions)
        {
            printf("Collision[%i] = { { %.1f, %.1f } , %.1f , { %.1f, %.1f} }; \n",
                i, elem.Length[0], elem.Length[1], elem.Angle[2], elem.Location[0], elem.Location[1]);
            ++i;
        }
    }

}

void MapEditor::Input()
{
    int input = 0;

    printf("[ 1. Image 변경 ]  [ 2. Speed 변경 ] \n");
    printf("Input : ");
    scanf_s("%d", &input);
    switch(input)
    {
        case 1 :
        {
            printf("변경할 이미지 이름을 입력하세요. \n");
            printf("Input : ");
            std::cin >> Str;
            strcpy_s(const_cast<char*>(Collisions.back().Content), Str.size() + 1, Str.c_str());
            
            break;
        }
    case 2 :
        {
            printf("변경할 스피드값을 입력하세요. \n");
            printf("Input : ");
            scanf_s("%f", &Value);
            Value *= 0.01f;
            break;
        }
    default :
        Input();
    }
}

void MapEditor::Operation()
{
    switch(Type)
    {
        case OperationType::OT_Location :
        {
            vector<2> Direction = { 0 , 0 };

            if (Input::Get::Key::Press(VK_UP))
                Direction[1] += 1;
            if (Input::Get::Key::Press(VK_DOWN))
                Direction[1] -= 1;
            if (Input::Get::Key::Press(VK_RIGHT))
                Direction[0] += 1;
            if (Input::Get::Key::Press(VK_LEFT))
                Direction[0] -= 1;

            if (length(Direction) != 0) Collisions.back().Location += normalize(Direction) * Value;
            break;
        }
        case OperationType::OT_Rotation :
        {
            if (Input::Get::Key::Press(VK_UP))
                Collisions.back().Angle[2] += 0.01f;
            if (Input::Get::Key::Press(VK_DOWN))
                Collisions.back().Angle[2] -= 0.01f;
            if (Input::Get::Key::Press(VK_RIGHT))
                Collisions.back().Angle[2] += 0.01f;
            if (Input::Get::Key::Press(VK_LEFT))
                Collisions.back().Angle[2] -= Value;
            break;
        }
        case OperationType::OT_Scale :
        {
            if (Input::Get::Key::Press(VK_UP))
                Collisions.back().Length[1] += Value;
            if (Input::Get::Key::Press(VK_DOWN))
                Collisions.back().Length[1] -= Value;
            if (Input::Get::Key::Press(VK_RIGHT))
                Collisions.back().Length[0] += Value;
            if (Input::Get::Key::Press(VK_LEFT))
                Collisions.back().Length[0] -= Value;
            break;
        }
    }
    vector<2> Direction = { 0 , 0 };

    if (Input::Get::Key::Press('A'))
        Direction[0] -= 1;
    if (Input::Get::Key::Press('D'))
        Direction[0] += 1;
    if (Input::Get::Key::Press('W'))
        Direction[1] += 1;
    if (Input::Get::Key::Press('S'))
        Direction[1] -= 1;

    if (length(Direction) != 0) Camera.Location += normalize(Direction) * 500 * Time::Get::Delta();
}

void MapEditor::Create()        
{
    Collisions.push_back(Rendering::Image::Component{ new char , { 100, 100 }, { 0 , 0 , 0 }, Camera.Location});
    strcpy_s(const_cast<char*>(Collisions.back().Content), Str.size() + 1, Str.c_str());
}





