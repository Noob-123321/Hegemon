#define SDL_MAIN_USE_CALLBACKS 1  /* Использовать функции обратного вызова вместо обычной main() */

#include "core/save.h"          // Подключение заголовочного файла для работы с сохранениями
#include "map/map.h"            // Подключение заголовочного файла для работы с картой
#include <SDL3/SDL.h>           // Основной заголовок SDL3
#include <SDL3/SDL_main.h>      // Заголовок SDL3 для точки входа с callback-архитектурой

/* Глобальные указатели на окно и рендерер, используемые во всех callback-функциях. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

/*
 * SDL_AppInit вызывается один раз при старте приложения.
 * Здесь выполняется инициализация SDL, создание окна и рендерера.
 * Возвращает SDL_APP_CONTINUE, если инициализация прошла успешно,
 * или SDL_APP_FAILURE в случае ошибки.
 */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    // Устанавливает метаданные приложения: название, версию, идентификатор
    SDL_SetAppMetadata("asd", "1.0", "com.example.renderer-clear");

    // Инициализирует подсистему SDL Video. При неудаче – логирует ошибку и завершает.
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Создаёт окно размером 640x480 с возможностью изменения размера и привязанный к нему 2D-рендерер.
    // Указатели на окно и рендерер записываются в глобальные переменные window и renderer.
    if (!SDL_CreateWindowAndRenderer("examples/renderer/clear", 640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Настраивает логическое представление рендерера:
    // устанавливает виртуальное разрешение 640x480 и режим масштабирования Letterbox.
    SDL_SetRenderLogicalPresentation(renderer, 640, 480, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    return SDL_APP_CONTINUE;  // Продолжаем выполнение программы
}

/*
 * SDL_AppEvent вызывается для каждого события SDL.
 * Здесь обрабатываются события клавиатуры, мыши, окна и т.п.
 * Возвращает SDL_APP_SUCCESS (завершение) при получении события выхода,
 * иначе SDL_APP_CONTINUE.
 */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    // Проверяет, является ли событие запросом на закрытие окна (например, Alt+F4 или клик по крестику)
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  // Завершаем программу, сообщая ОС об успехе
    }
    return SDL_APP_CONTINUE;  // Продолжаем работу
}

/*
 * SDL_AppIterate вызывается в каждом кадре, пока приложение работает.
 * Здесь происходит очистка экрана с плавно меняющимся цветом и отрисовка кадра.
 */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    // Получаем текущее время в секундах (SDL_GetTicks возвращает миллисекунды)
    const double now = ((double)SDL_GetTicks()) / 1000.0;  // Конвертация из миллисекунд в секунды

    // Вычисляем красную компоненту цвета фона: синусоида от времени, сдвиг и масштабирование в диапазон [0, 1]
    const float red = (float) (0.5 + 0.5 * SDL_sin(now));
    // Зелёная компонента: синус со сдвигом по фазе на 2π/3 относительно красной
    const float green = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    // Синяя компонента: синус со сдвигом на 4π/3
    const float blue = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));

    // Устанавливает цвет очистки рендерера в формате float RGBA (альфа = непрозрачность)
    SDL_SetRenderDrawColorFloat(renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);

    // Очищает текущий целевой буфер рендеринга (экран) установленным цветом
    SDL_RenderClear(renderer);

    // Показывает нарисованный кадр на экране (меняет местами буферы при двойной буферизации)
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;  // Продолжаем выполнение
}

/*
 * SDL_AppQuit вызывается один раз при завершении приложения.
 * Здесь можно освободить ресурсы, но в данной программе это не требуется.
 */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    // Ничего не делаем – SDL автоматически уничтожит окно и рендерер при выходе
}













//int main(int argc, char* argv[]) {
//    //готовность к запуску
//    //загрузить настройки
//
//    GameSettings settings = LoadGameSettings();
//
//    //std::cout << settings.fullscreen << std::endl;
//    //std::cout << settings.screenHeight << std::endl;
//    //std::cout << settings.screenWidth << std::endl;
//
//    //изменить настройки
//    settings.fullscreen = false;
//    settings.screenHeight = 1142789;
//    settings.screenWidth = 1148;
//
//    //сохранить настройки
//    SaveGameSettings(settings);
//
//    int bit = extract_bit("map.bin", 15);
//    std::cout << "Bit: " << bit << std::endl;
//    return 0;
//}
//asdsadasd

