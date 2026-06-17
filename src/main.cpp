#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

class $modify(DoubleJumpPlayer, PlayerObject) {
    struct Fields {
        bool m_usedDoubleJump = false;
    };

    void update(float dt) {
        PlayerObject::update(dt);
        if (m_isOnGround) {
            m_fields->m_usedDoubleJump = false;
        }
    }

    bool pushButton(PlayerButton btn) {
        if (!Mod::get()->getSettingValue<bool>("double-jump-enabled")) {
            return PlayerObject::pushButton(btn);
        }

        if (btn == PlayerButton::Jump && !m_isOnGround && !m_fields->m_usedDoubleJump) {
            m_fields->m_usedDoubleJump = true;
            m_yVelocity = 10.0;
            return true;
        }

        return PlayerObject::pushButton(btn);
    }
};
