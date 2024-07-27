#pragma once

class AWindowPage {
public:
    virtual ~AWindowPage() = default;
    virtual void show() = 0;
};
