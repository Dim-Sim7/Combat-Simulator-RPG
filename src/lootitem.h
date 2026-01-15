#pragma once

class LootItem : public Item, public IRDSObject {
public:
    LootItem(const std::string& name, int id)
        : Item(name, id, ITEMTYPE::MISC, 1, false) {}

    // ---- IRDSObject state ----
    double probability{1.0};
    bool unique{false};
    bool always{false};
    bool enabled{true};
    std::weak_ptr<RDSTable> table;

    // ---- IRDSObject interface ----
    double getProbability() const override { return probability; }
    void setProbability(double p) override { probability = p; }

    bool isUnique() const override { return unique; }
    void setUnique(bool u) override { unique = u; }

    bool isAlways() const override { return always; }
    void setAlways(bool a) override { always = a; }

    bool isEnabled() const override { return enabled; }
    void setEnabled(bool e) override { enabled = e; }

    std::weak_ptr<RDSTable> getTable() const override { return table; }
    void setTable(std::weak_ptr<RDSTable> t) override { table = t; }

    void onPreResultEvaluation(const EventArgs&) override {}
    void onHit(const EventArgs&) override {}
    void onPostResultEvaluation(const ResultEventArgs&) override {}

    std::string toString(int) const override {
        return getName();
    }
};
